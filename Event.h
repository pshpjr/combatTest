#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <typeindex>

#include "EventTypes.h" // CallbackID 정의가 포함된 헤더 가정

// 이벤트 시스템을 위한 간단하고 직관적인 구현
namespace EventSystem
{
	// 기본 이벤트 클래스: 가변 인자 템플릿을 사용한 콜백 관리
	template <typename... Args>
	class Event
	{
	public:
		using Callback = std::function<void(Args...)>;

		// 새 콜백을 등록하고 고유 ID 반환
		CallbackID Subscribe(Callback callback)
		{
			CallbackID id = GenerateCallbackId();
			callbacks_[id] = std::move(callback);
			return id;
		}

		// 등록된 콜백 해지
		void Unsubscribe(CallbackID id)
		{
			callbacks_.erase(id);
		}

		// 모든 콜백을 호출하여 이벤트 발생
		template <typename... FArgs>
		void Notify(FArgs&&... args) const
		{
			for (const auto& [_, cb] : callbacks_)
			{
				cb(std::forward<FArgs>(args)...);
			}
		}

	private:
		// 다음 사용 가능한 콜백 ID 생성
		CallbackID GenerateCallbackId()
		{
			return next_callback_id_++;
		}

		std::unordered_map<CallbackID, Callback> callbacks_; // 콜백 저장소
		CallbackID next_callback_id_ = 1; // ID 생성용 카운터
	};


	template <typename... Args>
	class EventHandle
	{
	public:
		explicit EventHandle(Event<Args...>* event) : event_(event)
		{
		}

		// 콜백 등록
		CallbackID Subscribe(typename Event<Args...>::Callback callback)
		{
			return event_ ? event_->Subscribe(std::move(callback)) : InvalidCallbackID;
		}

		// 콜백 해지
		void Unsubscribe(CallbackID id)
		{
			if (event_) event_->Unsubscribe(id);
		}

		// 이벤트 발생
		void Notify(Args... args) const
		{
			if (event_) event_->Notify(std::forward<Args>(args)...);
		}

		// 유효성 체크
		explicit operator bool() const
		{
			return event_ != nullptr;
		}

	private:
		Event<Args...>* event_; // 관리 대상 이벤트
	};

	// 키 기반 이벤트 관리자
	template <typename Key>
	class EventManager
	{
	private:
		// 이벤트의 기본 인터페이스
		struct EventBase
		{
			virtual ~EventBase() = default;
			virtual std::type_index GetTypeIndex() const = 0;
		};

		// 특정 이벤트 타입을 위한 래퍼
		template <typename... Args>
		struct TypedEvent : EventBase
		{
			Event<Args...> event;

			std::type_index GetTypeIndex() const override
			{
				return typeid(Event<Args...>);
			}
		};

	public:
		EventManager() = default;
		~EventManager() = default;

		// 기존 이벤트 핸들 가져오기 (없으면 무효 핸들 반환)
		template <typename... Args>
		EventHandle<Args...> GetEvent(const Key& key)
		{
			auto it = events_.find(key);
			if (it == events_.end())
			{
				return EventHandle<Args...>(nullptr);
			}
			auto* typed_event = static_cast<TypedEvent<Args...>*>(it->second.get());
			return EventHandle<Args...>(&typed_event->event);
		}

		// 이벤트가 없으면 생성 후 핸들 반환
		template <typename... Args>
		EventHandle<Args...> GetOrCreateEvent(const Key& key)
		{
			if (auto handle = GetEvent<Args...>(key))
			{
				return handle;
			}

			auto event = std::make_unique<TypedEvent<Args...>>();
			EventHandle<Args...> handle(&event->event);
			events_[key] = std::move(event);
			return handle;
		}

		// 지정된 키의 이벤트를 발생
		template <typename... Args>
		void Notify(const Key& key, Args&&... args)
		{
			if (auto handle = GetEvent<Args...>(key))
			{
				handle.Notify(std::forward<Args>(args)...);
			}
		}

	private:
		std::unordered_map<Key, std::unique_ptr<EventBase>> events_; // 이벤트 저장소
	};
} // namespace EventSystem
