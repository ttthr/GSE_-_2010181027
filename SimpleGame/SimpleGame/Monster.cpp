#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{

}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_Info.x = 100;
	m_Info.y = 100;
	m_Info.z = 0;
	m_Info.size = 20;

}

int  CMonster::Update(float _ElapsedTime)
{
	//타임 매니저 같은 역할을 하기 위한 변수 
	//float ElapsedTime = 0.1;


	m_Info.x += m_fspeed * m_xDir * _ElapsedTime;
	m_Info.y += m_fspeed * m_yDir * _ElapsedTime;

	if (m_Info.x > 250)
		m_xDir *= -1;
	else if (m_Info.x <= -250)
		m_xDir *= -1;


	if (m_Info.y > 250)
		m_yDir *= -1;
	else if (m_Info.y <= -250)
		m_yDir *= -1;

	return 0;
}



