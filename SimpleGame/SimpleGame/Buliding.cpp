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
	m_Info.r = 1;
	m_Info.g = 1;
	m_Info.b = 1;
	m_Info.a = 1;

	m_fLife = 500.f;
	m_fMaxLife = 500.f;
	m_fBulletShotTime = 1.f;
	m_fAttack = 1.f;
	m_fLifeTime = 10000.f;
}

int CBuliding::Update(float _ElapsedTime)
{
   
	//데드체크
	if (m_bDeadCheck == true)
		return 1;
	
	//3초마다 쏘게
	m_fBulletShotTime -= _ElapsedTime;

	//시간 지나면 객체 삭제
	m_fLifeTime -= _ElapsedTime;

	if (m_fLifeTime < 0)
		return 1;

	if (m_fBulletShotTime <= 0)
	{
	
	    m_pBulletList->push_back(CreateBullet());

		m_fBulletShotTime = 1.f;
	}

	return 0;
	
}

void CBuliding::SetBullet(list<CGameObject*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

CGameObject* CBuliding::CreateBullet()
{
	float fRadianAngle = float (rand() % 360 ) / 180 * 3.141592f;

	CGameObject *pBullet = new CBullet(m_Info.x + 57 * -cosf(fRadianAngle), m_Info.y + 57 * sinf(fRadianAngle), -cosf(fRadianAngle), sinf(fRadianAngle), 20 , 100 , 10);
	pBullet->Initialize();
	dynamic_cast<CBullet*>(pBullet)->SetType(OBJECT_ARROW_TEAM1);

	return pBullet;

}
