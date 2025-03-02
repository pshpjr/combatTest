#pragma once
#include "Component.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Angle.hpp>

class TransformComponent : public Component
{
public:
	TransformComponent(const sf::Vector2f& position = sf::Vector2f(0, 0),
	                   sf::Angle rotation = sf::degrees(0),
	                   const sf::Vector2f& scale = sf::Vector2f(1, 1))
		: m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
	}

	void Initialize() override
	{
	}

	void Update(float deltaTime) override
	{
	}

	[[nodiscard]] const sf::Vector2f& GetPosition() const
	{
		return m_Position;
	}

	void SetPosition(const sf::Vector2f& position)
	{
		m_Position = position;
	}

	[[nodiscard]] sf::Angle GetRotation() const
	{
		return m_Rotation;
	}

	void SetRotation(sf::Angle rotation)
	{
		m_Rotation = rotation;
	}

	[[nodiscard]] const sf::Vector2f& GetScale() const
	{
		return m_Scale;
	}

	void SetScale(const sf::Vector2f& scale)
	{
		m_Scale = scale;
	}

	[[nodiscard]] sf::Transform GetTransform() const
	{
		sf::Transform transform;
		transform.translate(m_Position);
		transform.rotate(m_Rotation);
		transform.scale(m_Scale);
		return transform;
	}

private:
	sf::Vector2f m_Position;
	sf::Angle m_Rotation;
	sf::Vector2f m_Scale;
	TYPEID_DEFINE("Transform")
};
