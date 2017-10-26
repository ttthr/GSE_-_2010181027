#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_Info.z = 0;
	m_Info.size = 5;
}

void CBullet::Update(float _ElapsedTime)
{
}
