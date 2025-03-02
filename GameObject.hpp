#pragma once
#include <vector>
#include <memory>
#include <typeindex>
#include "Component.hpp"
#include "Define.h"

using GUID = uint64;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject(GUID id) : m_Name(id)
	{
	}

	~GameObject() = default;

	void Initialize()
	{
		for (const auto& component : m_Components)
		{
			component->Initialize();
		}
	}

	void Update(float deltaTime)
	{
		for (const auto& component : m_Components)
		{
			component->Update(deltaTime);
		}
	}

	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

		auto component = std::make_unique<T>(std::forward<Args>(args)...);
		component->SetOwner(this);
		auto ret = component.get();

		m_Components.push_back(std::move(component));
		return ret;
	}

	template <typename T>
	T* GetComponent()
	{
		static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

		for (const auto& component : m_Components)
		{
			if (component->GetTypeID() == T::TypeID())
			{
				return static_cast<T*>(component.get());
			}
		}

		return nullptr;
	}

	const GUID GetGUID() const
	{
		return m_Name;
	}

private:
	GUID m_Name;
	std::vector<std::unique_ptr<Component>> m_Components;
};
