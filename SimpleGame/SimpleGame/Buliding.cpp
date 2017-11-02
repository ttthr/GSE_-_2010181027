#include "stdafx.h"
#include "Buliding.h"

CBuliding::CBuliding()
{

}


CBuliding::~CBuliding()
{
}

void CBuliding::Initialize(void)
{
	m_Info.x = 0;
	m_Info.y = 0;
	m_Info.z = 0;
	m_Info.size = 80;
	m_Info.r = 255;
	m_Info.g = 255;
	m_Info.b = 0;
	m_Info.a = 255;

	m_fLife = 500;
	m_fBulletShotTime = 3.f;

}

int CBuliding::Update(float _ElapsedTime)
{


	m_fBulletShotTime -= _ElapsedTime;

	if (m_fBulletShotTime <= 0)
	{
		m_pBulletList->push_back(CreateBullet());

		m_fBulletShotTime = 3.f;
	}
	//����üũ

	return  CGameObject::Update(_ElapsedTime);
	
}

void CBuliding::SetBullet(list<CGameObject*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

CGameObject* CBuliding::CreateBullet()
{
	float fRadianAngle = float (rand() % 360 ) / 180 * 3.141592f;

	CGameObject *pBullet = new CBullet(m_Info.x + 57 * -cosf(fRadianAngle), m_Info.y + 57 * sinf(fRadianAngle), -cosf(fRadianAngle), sinf(fRadianAngle), 20);
	pBullet->Initialize();
	dynamic_cast<CBullet*>(pBullet)->SetType(OBJECT_ARROW);

	return pBullet;

}
