#include "TransformComponent.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "CollisionComponent.h"
#include "GameObject.h"

namespace psh::component
{
	TransformComponent::TransformComponent(const sf::Vector2f& position, sf::Angle rotation, bool isCircle): m_isCircle(
		isCircle)
	{
		if (isCircle)
		{
			m_shape = new sf::CircleShape;
		}
		else
		{
			m_shape = new sf::RectangleShape;
		}
	}

	void TransformComponent::Initialize()
	{
		m_collision = GetOwner()->GetComponent<CollisionComponent>();
	}

	void TransformComponent::Update(MsTime deltaTime)
	{
	}

	sf::Vector2f TransformComponent::GetPosition() const
	{
		return m_shape->getPosition();
	}

	void TransformComponent::SetPosition(sf::Vector2f position)
	{
		m_shape->setPosition(position);
		if (m_collision)
		{
			m_collision->SetPosition(position);
		}
	}

	sf::Angle TransformComponent::GetRotation() const
	{
		return m_shape->getRotation();
	}

	void TransformComponent::SetRotation(sf::Angle rotation)
	{
		m_shape->setRotation(rotation);
		if (m_collision)
		{
			m_collision->SetRotation(rotation);
		}
	}

	sf::Vector2f TransformComponent::GetSize() const
	{
		return m_size;
	}

	void TransformComponent::SetSize(sf::Vector2f size)
	{
		m_size = size;

		if (m_isCircle)
		{
			auto shape = static_cast<sf::CircleShape*>(m_shape);
			shape->setRadius(size.x);
			shape->setOrigin({size.x, size.y});
		}
		else
		{
			static_cast<sf::RectangleShape*>(m_shape)->setSize(size);
			m_shape->setOrigin({size.x / 2, size.y / 2});
		}
		auto texture = m_shape->getTexture();
		if (m_collision)
		{
			m_collision->SetSize(size);
		}
	}

	sf::Transform TransformComponent::GetTransform() const
	{
		return m_shape->getTransform();
	}

	bool TransformComponent::isCircle() const
	{
		return m_isCircle;
	}

	sf::Shape* TransformComponent::GetShape()
	{
		return m_shape;
	}

	void TransformComponent::Move(sf::Vector2f offset)
	{
		m_shape->move(offset);

		if (m_collision)
		{
			m_collision->SetPosition(GetPosition() + offset);
		}
	}

	void TransformComponent::Rotate(sf::Angle angle)
	{
		m_shape->rotate(angle);

		if (m_collision)
		{
			m_collision->SetRotation(GetRotation() + angle);
		}
	}

	void TransformComponent::Scale(sf::Vector2f factor)
	{
		m_shape->scale(factor);
	}
}
