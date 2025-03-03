#pragma once
#include "Component.h"
#include "Define.h"
#include "GameManager.h"

namespace psh::Component
{
	class MovementComponent;
}

namespace sf
{
	class Event;
}

namespace psh
{
	enum class InputEvent : uint8;

	namespace Component
	{
		class TransformComponent;

		class InputComponent : public Component
		{
		public:
			InputComponent() = default;

			void Initialize() override;

			void Update(MsTime deltaTime) override;

			void HandleEvent(InputType type, const sf::Event* event) const;

		private:
			MovementComponent* m_movement;
			COMPONENT_DEFINE("Input")
		};
	}
}
