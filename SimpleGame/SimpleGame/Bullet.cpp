#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(float _PosX, float _PosY)
{
 	
	m_Info.x = _PosX;
	m_Info.y = _PosY;

}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_Info.z = 0;
	m_Info.size = 5;
	m_fSpeed = 0.1f;
	m_fAttack = 1.0f;
	//m_Info.r = 155;
	//m_Info.g = 0;
	//m_Info.b = 0;
	//m_Info.a = 0;
}

int CBullet::Update(float _ElapsedTime)
{
	//�Ѿ� ������ ����
	Dir();
	//�Ѿ� Ÿ��
	Type();

	return 0;

}

void CBullet::Dir()
{
	switch (m_eType)
	{
	case DIR_RIGHT:
		m_Info.x += m_fSpeed;
		break;
	case DIR_LEFT:
		m_Info.x -= m_fSpeed;
		break;
	case DIR_UP:
		m_Info.y += m_fSpeed;
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
		m_Info.y -= m_fSpeed;
		break;
	case DIR_DOWN_L:
		m_Info.x += m_fSpeed;
		m_Info.y += m_fSpeed;
		break;
	case DIR_DOWN_R:
		m_Info.x -= m_fSpeed;
		m_Info.y += m_fSpeed;
		break;
	}
}

void CBullet::Type()
{
	switch (m_eBulletType)
	{
	case OBJECT_BULLET:
		m_Info.r = 255;
		m_Info.g = 0;
		m_Info.b = 0;
		m_Info.a = 255;
		break;
	case OBJECT_ARROW:
		m_Info.r = 0;
		m_Info.g = 150;
		m_Info.b = 255;
		m_Info.a = 255;
		break;

	}
}