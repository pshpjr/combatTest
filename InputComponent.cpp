#include "InputComponent.h"

#include <iostream>
#include <stdexcept>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "GameManager.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "TransformComponent.h"

namespace psh::component
{
	void InputComponent::Initialize()
	{
		m_movement = GetOwner()->GetRequiredComponent<MovementComponent>();
	}

	void InputComponent::Update(MsTime deltaTime)
	{
	}

	void InputComponent::HandleEvent(InputType type, const sf::Event* event) const
	{
		switch (type)
		{
		case InputType::Keyboard:
			{
				auto keyEvent = event->getIf<sf::Event::KeyPressed>();
				auto mousePosition = sf::Mouse::getPosition();
			}
			break;
		case InputType::Mouse:
			{
				auto e = event->getIf<sf::Event::MouseButtonPressed>();
				const sf::Vector2f clickPosition(static_cast<float>(e->position.x), static_cast<float>(e->position.y));
				m_movement->Move(clickPosition);
				std::cout << "mouse pressed\n";
			}
			break;
		}
	}
}
