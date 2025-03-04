/* 
EffectComponent
Created by: pshpjr
Date: 2025-03-03

Description: 

*/

#pragma once
#include "Component.h"

//STL 헤더

//서드파티 헤더

namespace sf
{
	class RenderWindow;
}

//프로젝트 헤더
namespace psh::component
{
	class EffectComponent : public Component
	{
	public:
		EffectComponent();
		~EffectComponent() override;
		void Draw(sf::RenderWindow& window);
		//AddEffect(location, shape, duration);
		//캐릭터 정면 기준 상대위치로
		COMPONENT_DEFINE("Effect")
	};
}
