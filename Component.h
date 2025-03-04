#pragma once
#include "Time.h"
#include "ComponentTypeRegistry.h"

namespace psh
{
	class GameObject;

	namespace component
	{
		using ComponentTypeID = size_t;

		class Component
		{
		public:
			Component() = default;
			virtual ~Component() = default;

			virtual void Initialize()
			{
			}

			virtual void Update(MsTime deltaTime)
			{
			}

			void SetOwner(GameObject* owner)
			{
				m_Owner = owner;
			}

			[[nodiscard]] GameObject* GetOwner() const
			{
				return m_Owner;
			}

			[[nodiscard]] virtual ComponentTypeID GetTypeID() const = 0;

		private:
			GameObject* m_Owner;
		};
	}
}
