#include "GameObject.h"

namespace psh
{
	GameObject::GameObject(GUID id): m_name(id)
	{
	}

	void GameObject::Initialize()
	{
		for (auto& component : m_components)
		{
			component->Initialize();
		}
	}

	void GameObject::Update(MsTime deltaTime)
	{
		for (auto& component : m_components)
		{
			component->Update(deltaTime);
		}
	}

	GUID GameObject::GetGUID() const
	{
		return m_name;
	}
}
