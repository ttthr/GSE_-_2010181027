#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(float _PlayerPosX, float _PlayerPosY)
{
 	m_Info.x = _PlayerPosX;
	m_Info.y = _PlayerPosY;
	m_Info.z = 0;
	m_Info.size = 5;
	m_fSpeed = 1;
	m_Info.r = 255;
	m_Info.g = 0;
	m_Info.b = 0;
	m_Info.a = 0;
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_Info.z = 0;
	m_Info.size = 5;

	m_fSpeed = 0.5;
}

int CBullet::Update(float _ElapsedTime)
{
	switch (m_eType)
	{
	case DIR_RIGHT:
		m_Info.x += m_fSpeed;
		break;

	case DIR_LEFT:
		m_Info.y -= m_fSpeed;
		break;

	case DIR_UP:
		m_Info.y -= m_fSpeed;
		break;

	case DIR_UP_L:
		m_Info.y -= m_fSpeed;
		m_Info.x -= m_fSpeed;
		break;

	case DIR_UP_R:
		m_Info.y -= m_fSpeed;
		m_Info.x += m_fSpeed;
		break;

	case DIR_DOWN:
		m_Info.y += m_fSpeed;
		break;
	}

	return 0;

}
