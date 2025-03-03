#include "GameObject.h"

namespace psh
{
	GameObject::GameObject(GUID id): m_name(id)
	{
	}

	void GameObject::Initialize() const
	{
		for (const auto& component : m_components)
		{
			component->Initialize();
		}
	}

	void GameObject::Update(MsTime deltaTime) const
	{
		for (const auto& component : m_components)
		{
			component->Update(deltaTime);
		}
	}

	GUID GameObject::GetGUID() const
	{
		return m_name;
	}
}
