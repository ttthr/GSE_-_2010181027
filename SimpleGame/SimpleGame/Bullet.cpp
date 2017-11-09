#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(float _PosX, float _PosY, float _DirX, float _DirY, float fAttack)
{
 	
	m_Info.x = _PosX;
	m_Info.y = _PosY;
	m_fAttack = fAttack;
	m_xDir = _DirX;
	m_yDir = _DirY;

}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_Info.z = 0;
	m_Info.size = 5;
	m_fSpeed = 300.f;
	m_fAttack = 10.f;
	m_fLife = 0.7f;
   
}

int CBullet::Update(float _ElapsedTime)
{
	//���� üũ
	if (m_bDeadCheck == true)
	{
		return 1;
	}
	//�Ѿ� ������ ���� ����
	m_fLife -= _ElapsedTime;

	if (m_fLife < 0)
		return 1;
	
	//�Ѿ� ������ ����
	Move(_ElapsedTime);

	return 0;

}

void CBullet::Move(float _ElapsedTime)
{
	m_Info.x += m_fSpeed * m_xDir * _ElapsedTime;
	m_Info.y += m_fSpeed * m_yDir * _ElapsedTime;
}

