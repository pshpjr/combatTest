#include "CollisionComponent.h"
#include <chipmunk/chipmunk.h>
#include "GameObject.h"
#include "TransformComponent.h"

void psh::component::CollisionComponent::Initialize()
{
	m_transform = GetOwner()->GetRequiredComponent<TransformComponent>();
	SetPosition(m_transform->GetPosition());
	SetRotation(m_transform->GetRotation());
	SetSize(m_transform->GetSize());
}

void psh::component::CollisionComponent::Update(MsTime deltaTime)
{
	Component::Update(deltaTime);
}

void psh::component::CollisionComponent::SetPosition(sf::Vector2f pos)
{
	cpBodySetPosition(m_body, cpv(pos.x, pos.y));
}

void psh::component::CollisionComponent::SetRotation(sf::Angle angle)
{
	cpBodySetAngle(m_body, angle.asRadians());
}

void psh::component::CollisionComponent::SetSize(sf::Vector2f size)
{
	if (m_isCircle)
	{
		float radius = size.x / 2.0f;
		m_shape = cpCircleShapeNew(m_body, radius, cpvzero);
	}
	else
	{
		m_shape = cpBoxShapeNew(m_body, size.x, size.y, 0.0);
	}
}

bool psh::component::CollisionComponent::CheckCollision(CollisionComponent& other) const
{
	return cpShapesCollide(m_shape, other.m_shape).count > 0;
}

psh::component::CollisionComponent::CollisionComponent()
{
	m_body = cpBodyNewStatic();
	cpBodySetPosition(m_body, {0, 0});
	cpBodySetAngle(m_body, 0);
}

psh::component::CollisionComponent::~CollisionComponent()
{
	cpShapeFree(m_shape);
	cpBodyFree(m_body);
}
