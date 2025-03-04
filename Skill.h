/* 
Skill
Created by: pshpjr
Date: 2025-03-03

Description: 

*/

#pragma once
#include "Time.h"

//STL 헤더

//서드파티 헤더

//프로젝트 헤더

class Skill
{
public:
	Skill();
	~Skill();

private:
	Timer m_cooldown;
	//범위
	//데미지
	//타입 (투사체, 즉발, 범위)
};

/*
 * 플레이어-> 공격 컴포넌트 -> 어떤 공격을 하겠다 -> 해당 공격 있나?
 * 있으면 스킬에서 정보 받아옴 -> 
 *
 *
 *
 */
