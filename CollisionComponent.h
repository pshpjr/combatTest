/* 
CollisionComponent
Created by: pshpjr
Date: 2025-03-03

Description: 

*/

#pragma once

//STL 헤더

//서드파티 헤더

#include <SFML/System/Vector2.hpp>

#include "Component.h"

//프로젝트 헤더
struct cpBody;
struct cpShape;

namespace psh::component
{
	class TransformComponent;

	class CollisionComponent : public Component
	{
	public:
		CollisionComponent();

		~CollisionComponent() override;

		void Initialize() override;

		void Update(MsTime deltaTime) override;

		void SetPosition(sf::Vector2f pos);

		void SetRotation(sf::Angle angle);

		void SetSize(sf::Vector2f size);

		bool CheckCollision(CollisionComponent& other) const;

	private:
		cpBody* m_body{nullptr};
		cpShape* m_shape{nullptr};
		bool m_isCircle{false};
		TransformComponent* m_transform{nullptr};
		COMPONENT_DEFINE("Collision")
	};
}
