#pragma once
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.h"

namespace psh::component
{
	class CollisionComponent;
}

namespace sf
{
	class Shape;
}

namespace psh::component
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(const sf::Vector2f& position = sf::Vector2f(0, 0),
		                   sf::Angle rotation = sf::degrees(0),
		                   bool isCircle = false);

		void Initialize() override;

		void Update(MsTime deltaTime) override;

		[[nodiscard]] sf::Vector2f GetPosition() const;

		void SetPosition(sf::Vector2f position);

		[[nodiscard]] sf::Angle GetRotation() const;

		void SetRotation(sf::Angle rotation);

		[[nodiscard]] sf::Vector2f GetSize() const;

		void SetSize(sf::Vector2f);

		[[nodiscard]] sf::Transform GetTransform() const;

		[[nodiscard]] bool isCircle() const;

		[[nodiscard]] sf::Shape* GetShape();

		void Move(sf::Vector2f offset);

		void Rotate(sf::Angle angle);

		void Scale(sf::Vector2f factor);

	private:
		bool m_isCircle = false;
		sf::Vector2f m_size;
		sf::Shape* m_shape;
		CollisionComponent* m_collision{nullptr};
		COMPONENT_DEFINE("Transform")
	};
}
