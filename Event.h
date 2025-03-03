#pragma once
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "EventTypes.h"

namespace psh::EventSystem
{
	template <typename... Args>
	class Event
	{
	public:
		using Callback = std::function<void(Args...)>;

		// 새 콜백을 등록하고 고유 CallbackID 반환
		CallbackID Subscribe(Callback callback)
		{
			CallbackID id = GenerateCallbackId();
			m_callbacks[id] = std::move(callback);
			return id;
		}

		// 등록된 콜백 해지
		void Unsubscribe(CallbackID id)
		{
			m_callbacks.erase(id);
		}


		// 모든 콜백을 호출하여 이벤트 발생
		template <typename... FArgs>
		void Notify(FArgs&&... args) const
		{
			for (const auto& [_, cb] : m_callbacks)
			{
				cb(std::forward<FArgs>(args)...);
			}
		}

	private:
		// 다음 사용 가능한 콜백 TypeID 생성
		CallbackID GenerateCallbackId()
		{
			return m_next_callback_id++;
		}

		std::unordered_map<CallbackID, Callback> m_callbacks;
		CallbackID m_next_callback_id = 1;
	};


	/**
	 * \brief 유효한지 bool 체크 가능. 무효인 경우 Notify, Subscribe 작동 안 함.
	 * \note 내부에서 사용하는 이벤트 포인터 노출시키기 싫었음
	 */
	template <typename... Args>
	class EventHandle
	{
	public:
		explicit EventHandle(Event<Args...>* event) : m_event(event)
		{
		}

		/**
		 * \return 해당 콜백의 ID. 구독 해제시 사용. 무효 핸들이면 InvalidCallbackID 리턴
		 */
		CallbackID Subscribe(typename Event<Args...>::Callback callback)
		{
			return m_event ? m_event->Subscribe(std::move(callback)) : InvalidCallbackID;
		}

		void Unsubscribe(CallbackID id)
		{
			if (m_event)
			{
				m_event->Unsubscribe(id);
			}
		}

		void Notify(Args... args) const
		{
			if (m_event)
			{
				m_event->Notify(std::forward<Args>(args)...);
			}
		}

		explicit operator bool() const
		{
			return m_event != nullptr;
		}

	private:
		Event<Args...>* m_event;
	};


	/**
	 * \brief 키 값에 따라 연결된 이벤트를 트리거하는 이벤트 매니저
	 * \tparam Key 이벤트 구별할 키 타입
	 * \throws AccessViolation Triger 함수 인자 개수가 안 맞으면 런타임에 invoke 내부에서 에러 발생.
	 * \code
	 * // 사용 예시:
	 * // 1. 이벤트 생성 또는 가져오기
	 * auto mouseEvent = m_eventManager.GetOrCreateEvent<InputEvent, sf::Event*>(InputEvent::MousePressed);
	 *
	 * // 2. 이벤트 구독
	 * mouseEvent.Subscribe([](InputEvent type, sf::Event* e) {
	 *     input->HandleEvent(type, e); // 입력 처리
	 * });
	 *
	 * // 3. 이벤트 트리거 (인자 개수에 유의)
	 * m_eventManager.Notify(InputEvent::MousePressed, InputEvent::MousePressed, &event.value());
	 * \endcode
	 */
	template <typename Key>
	class EventManager
	{
		// 이벤트의 기본 인터페이스
		struct EventBase
		{
			virtual ~EventBase() = default;
			[[nodiscard]] virtual std::type_index GetTypeIndex() const = 0;
		};

		// 특정 이벤트 타입을 위한 래퍼
		template <typename... Args>
		struct TypedEvent : EventBase
		{
			static constexpr std::size_t ArgCount = sizeof...(Args);

			Event<Args...> event;

			[[nodiscard]] std::type_index GetTypeIndex() const override
			{
				return typeid(Event<Args...>);
			}
		};

	public:
		EventManager() = default;
		~EventManager() = default;


		/**
		 * \brief 키에 등록된 이벤트를 들고 옴. 이벤트가 없을 경우 무효 핸들 리턴. 
		 * \param key 해당 이벤트가 등록된 키
		 * \return 이밴트의 래퍼 
		 */
		template <typename... Args>
		EventHandle<Args...> GetEvent(const Key& key)
		{
			auto it = m_events.find(key);
			if (it == m_events.end())
			{
				return EventHandle<Args...>(nullptr);
			}
			auto* typed_event = static_cast<TypedEvent<Args...>*>(it->second.get());
			return EventHandle<Args...>(&typed_event->event);
		}

		template <typename... Args>
		EventHandle<Args...> GetOrCreateEvent(const Key& key)
		{
			if (auto handle = GetEvent<Args...>(key))
			{
				return handle;
			}

			auto event = std::make_unique<TypedEvent<Args...>>();
			EventHandle<Args...> handle(&event->event);
			m_events[key] = std::move(event);
			return handle;
		}

		template <typename... Args>
		void Notify(const Key& key, Args&&... args)
		{
			if (auto handle = GetEvent<Args...>(key))
			{
				handle.Notify(std::forward<Args>(args)...);
			}
		}

	private:
		std::unordered_map<Key, std::unique_ptr<EventBase>> m_events;
	};
} // namespace psh::EventSystem
