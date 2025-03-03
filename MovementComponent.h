/* 
MovementComponent
Created by: pshpjr
Date: 2025-03-03

Description: 

*/

#pragma once
#include <SFML/System/Vector2.hpp>

#include "Component.h"

//STL 헤더

//서드파티 헤더

namespace psh::Component
{
	class TransformComponent;
}

//프로젝트 헤더
namespace psh::Component
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent();
		~MovementComponent() override;

		void Initialize() override;
		void Update(MsTime deltaTime) override;
		void Move(sf::Vector2f destination);
		void Stop();

	private:
		TransformComponent* m_transform = nullptr;

		bool m_isMove = false;
		sf::Vector2f m_destination{0, 0};
		int m_moveSpeedMs = 1;

		COMPONENT_DEFINE("Movement")
	};
}
