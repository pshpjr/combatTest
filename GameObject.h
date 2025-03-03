#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include "Define.h"
#include "Time.h"

using GUID = uint64;

namespace psh
{
	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		explicit GameObject(GUID id);

		~GameObject() = default;

		void Initialize();

		void Update(MsTime deltaTime);

		GUID GetGUID() const;

		template <typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of_v<Component::Component, T>, "T must derive from Component");

			auto component = std::make_unique<T>(std::forward<Args>(args)...);
			component->SetOwner(this);
			auto ret = component.get();

			m_components.push_back(std::move(component));
			return ret;
		}

		template <typename T>
		T* GetComponent()
		{
			static_assert(std::is_base_of_v<Component::Component, T>, "T must derive from Component");

			for (const auto& component : m_components)
			{
				if (component->GetTypeID() == T::TypeID())
				{
					return static_cast<T*>(component.get());
				}
			}

			return nullptr;
		}

		template <typename T>
		bool HasComponent() const
		{
			return GetComponent<T>() != nullptr;
		}

		/**
		 * \brief 반드시 있어야 하는 컴포넌트 얻어올 때
		 * \throw runtime_error 
		 */
		template <typename T>
		T* GetRequiredComponent()
		{
			T* ret = GetComponent<T>();
			if (!ret)
			{
				throw std::runtime_error(std::format("requireComponent {} is missing", typeid(T).name()));
			}
			return ret;
		}

	private:
		GUID m_name;
		std::vector<std::unique_ptr<Component::Component>> m_components;
	};
}
