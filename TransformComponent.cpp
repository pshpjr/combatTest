#include "TransformComponent.h"

namespace psh::Component
{
	TransformComponent::TransformComponent(const sf::Vector2f& position, sf::Angle rotation, const sf::Vector2f& scale):
		m_Position(position), m_Rotation(rotation), m_Scale(scale)
	{
	}

	void TransformComponent::Initialize()
	{
	}

	void TransformComponent::Update(MsTime deltaTime)
	{
	}

	const sf::Vector2f& TransformComponent::GetPosition() const
	{
		return m_Position;
	}

	void TransformComponent::SetPosition(const sf::Vector2f& position)
	{
		m_Position = position;
	}

	sf::Angle TransformComponent::GetRotation() const
	{
		return m_Rotation;
	}

	void TransformComponent::SetRotation(sf::Angle rotation)
	{
		m_Rotation = rotation;
	}

	const sf::Vector2f& TransformComponent::GetScale() const
	{
		return m_Scale;
	}

	void TransformComponent::SetScale(const sf::Vector2f& scale)
	{
		m_Scale = scale;
	}

	sf::Transform TransformComponent::GetTransform() const
	{
		sf::Transform transform;
		transform.translate(m_Position);
		transform.rotate(m_Rotation);
		transform.scale(m_Scale);
		return transform;
	}
}
