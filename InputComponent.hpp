#pragma once
#include "Component.hpp"
#include "TransformComponent.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

class InputComponent : public Component
{
public:
	InputComponent() = default;

	void Initialize() override
	{
		m_Transform = GetOwner()->GetComponent<TransformComponent>();
		if (!m_Transform)
		{
			throw std::runtime_error("InputComponent requires a TransformComponent");
		}
	}

	void Update(float deltaTime) override
	{
	}

	void HandleEvent(psh::InputEvent type, sf::Event* event)
	{
		auto& e = *event->getIf<sf::Event::MouseButtonPressed>();
		const sf::Vector2f clickPosition(e.position.x, e.position.y);
		if (m_Transform)
		{
			// Calculate the angle between the object and the click position
			const sf::Vector2f objectPosition = m_Transform->GetPosition();
			const float dx = clickPosition.x - objectPosition.x;
			const float dy = clickPosition.y - objectPosition.y;
			const sf::Angle angle = sf::degrees(std::atan2(dy, dx) * 180 / sf::priv::pi);

			m_Transform->SetRotation(angle);
		}
		std::cout << "mouse pressed\n";
		//if (event.type == sf::Event::MouseButtonPressed && 
		//    event.mouseButton.button == sf::Mouse::Button::Left) {
		//    
		//    sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);
		//    
		//    if (m_Transform) {
		//        // Calculate the angle between the object and the click position
		//        sf::Vector2f objectPosition = m_Transform->GetPosition();
		//        float dx = clickPosition.x - objectPosition.x;
		//        float dy = clickPosition.y - objectPosition.y;
		//        sf::Angle angle = sf::degrees(std::atan2(dy, dx) * 180 / sf::priv::pi);
		//        
		//        m_Transform->SetRotation(angle);
		//    }
		//}
	}

private:
	TransformComponent* m_Transform;
	TYPEID_DEFINE("Input")
};
