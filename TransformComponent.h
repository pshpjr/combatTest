#pragma once
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.h"

namespace psh::Component
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(const sf::Vector2f& position = sf::Vector2f(0, 0),
		                   sf::Angle rotation = sf::degrees(0),
		                   const sf::Vector2f& scale = sf::Vector2f(1, 1));

		void Initialize() override;

		void Update(MsTime deltaTime) override;

		[[nodiscard]] const sf::Vector2f& GetPosition() const;

		void SetPosition(const sf::Vector2f& position);

		[[nodiscard]] sf::Angle GetRotation() const;

		void SetRotation(sf::Angle rotation);

		[[nodiscard]] const sf::Vector2f& GetScale() const;

		void SetScale(const sf::Vector2f& scale);

		[[nodiscard]] sf::Transform GetTransform() const;

	private:
		sf::Vector2f m_Position;
		sf::Angle m_Rotation;
		sf::Vector2f m_Scale;
		TYPEID_DEFINE("Transform")
	};
}
