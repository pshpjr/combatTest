#include "MovementComponent.h"

#include <valarray>

#include "GameObject.h"
#include "TransformComponent.h"

float Distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return std::sqrt(dx * dx + dy * dy);
}

bool approximatelyEqual(float a, float b, float relEpsilon = 1e-6f)
{
	float diff = std::abs(a - b);

	float maxVal = std::max({std::abs(a), std::abs(b), 1.0f});
	float adjustedEpsilon = relEpsilon * maxVal;

	return diff <= adjustedEpsilon;
}

float Norm(const sf::Vector2f& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

bool approximatelyEqual(sf::Vector2f v1, sf::Vector2f v2, float relEpsilon = 1e-6f)
{
	float diff = Distance(v1, v2);

	// 상대 오차 체크: 값의 크기에 따라 epsilon 조정
	float maxMagnitude = std::max({Norm(v1), Norm(v2), 1.0f}); // 0에 가까운 값 보정

	return diff <= maxMagnitude * relEpsilon;
}

psh::component::MovementComponent::MovementComponent()
{
}

psh::component::MovementComponent::~MovementComponent()
{
}

void psh::component::MovementComponent::Update(MsTime deltaTime)
{
	if (!m_isMove)
	{
		return;
	}
	const auto moveLen = m_moveSpeedMs * deltaTime;
	const auto distance = Distance(m_transform->GetPosition(), m_destination);

	//이번 업데이트로 갈 수 있는 범위면 도착
	if (distance <= moveLen)
	{
		m_isMove = false;
		m_transform->SetPosition(m_destination);
		return;
	}

	const auto position = m_transform->GetPosition();
	const auto rotation = m_transform->GetRotation().asRadians();
	const float dx = moveLen * cos(rotation);
	const float dy = moveLen * sin(rotation);

	m_transform->SetPosition({position.x + dx, position.y + dy});
}

void psh::component::MovementComponent::Move(sf::Vector2f destination)
{
	m_destination = destination;
	m_isMove = true;
	const sf::Vector2f position = m_transform->GetPosition();
	const float dx = destination.x - position.x;
	const float dy = destination.y - position.y;
	const auto radian = std::atan2(dy, dx);

	m_transform->SetRotation(sf::radians(radian));
}

void psh::component::MovementComponent::Stop()
{
	m_isMove = false;
}

void psh::component::MovementComponent::SetSpeed(float speed)
{
	m_moveSpeedMs = speed;
}

float psh::component::MovementComponent::GetSpeed() const
{
	return m_moveSpeedMs;
}

bool psh::component::MovementComponent::IsMoving() const
{
	return m_isMove;
}

sf::Vector2f psh::component::MovementComponent::GetDestination() const
{
	return m_destination;
}

void psh::component::MovementComponent::Initialize()
{
	m_transform = GetOwner()->GetRequiredComponent<TransformComponent>();
	m_destination = m_transform->GetPosition();
}
