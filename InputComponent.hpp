#pragma once
#include "Component.hpp"
#include "TransformComponent.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
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

	void HandleEvent(const sf::Event& event)
	{
		auto& e = *event.getIf<sf::Event::MouseButtonPressed>();
		event.visit([this](auto&& value)
		{
			using T = std::decay_t<decltype(value)>;
			if constexpr (std::is_same_v<T, sf::Event::MouseButtonPressed>)
			{
				if (value.button != sf::Mouse::Button::Left)
				{
					return;
				}

				sf::Vector2f clickPosition(value.position.x, value.position.y);
				if (m_Transform)
				{
					// Calculate the angle between the object and the click position
					sf::Vector2f objectPosition = m_Transform->GetPosition();
					float dx = clickPosition.x - objectPosition.x;
					float dy = clickPosition.y - objectPosition.y;
					sf::Angle angle = sf::degrees(std::atan2(dy, dx) * 180 / sf::priv::pi);

					m_Transform->SetRotation(angle);
				}
				std::cout << "mouse pressed\n";
			}
		});
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
	std::shared_ptr<TransformComponent> m_Transform;
};
