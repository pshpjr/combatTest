#pragma once
#include "Component.h"
#include "Define.h"

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

			void HandleEvent(InputEvent type, const sf::Event* event) const;

		private:
			TransformComponent* m_Transform;
			TYPEID_DEFINE("Input")
		};
	}
}
