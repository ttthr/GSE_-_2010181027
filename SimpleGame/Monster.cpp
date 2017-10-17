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
	m_Info.m_fx = 0;
	m_Info.m_fy = 100;
	m_Info.m_FCX = 30;
	m_Info.m_FCY = 30;

	m_fSpeed = 0.7f;
}

void CMonster::Update(void)
{
	
	if (m_Info.m_fx <= 250 )
	{
		m_Info.m_fx += m_fSpeed;
	}
}
