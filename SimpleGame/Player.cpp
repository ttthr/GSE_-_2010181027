#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{	
	
}

CPlayer::~CPlayer()
{


}

void CPlayer::Initialize(void)
{
    m_Info.m_fx = 30;
	m_Info.m_fy = 30;
	m_Info.m_FCX = 40;
	m_Info.m_FCY = 40;

	m_fSpeed = 0.5f;

}

void CPlayer::Update(void)
{
	if (GetAsyncKeyState(VK_RIGHT)& 0x8001)
	{
		m_Info.m_fx +=  m_fSpeed;
		
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		m_Info.m_fx -= m_fSpeed;
	
	}
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		m_Info.m_fy += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		m_Info.m_fy -= m_fSpeed;
	}


}

