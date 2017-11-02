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
	m_Info.z = 0;
	m_Info.size = 20;
	m_Info.r = 255;
	m_Info.g = 255;
	m_Info.b = 255;
	m_Info.a = 255;

	m_fAttack = 50.f;
	m_fLife =  20.0f;
	m_fSpeed = 100.0f;
	m_fBulletShotTime = 5.f;

	// 몬스터들 자동으로 이동 
	// 랜덤한 방향 설정
	float randx;
	float randy;
	while (1)
	{
		randx = float(rand() % 3 - 1);
		randy = float(rand() % 3 - 1);


		if (randx == 0 && randy == 0)
			continue;
		else
			break;

		m_xDir = randx;
		m_yDir = randy;
	}

}

int  CMonster::Update(float _ElapsedTime)
{
	//몬스터 이동 
	Move(_ElapsedTime);

	m_fBulletShotTime -= _ElapsedTime;

	if (m_fBulletShotTime <= 0)
	{
		m_pBulletList->push_back(CreateBullet());
		m_fBulletShotTime = 10.f;
	}
	//데드체크
	return  CGameObject::Update(_ElapsedTime);
}

void CMonster::SetBullet(list<CGameObject*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

CGameObject* CMonster::CreateBullet()
{
	float fRadianAngle = float(rand() % 360) / 180 * 3.141592f;

	CGameObject *pBullet = new CBullet(m_Info.x + 20 * -cosf(fRadianAngle), m_Info.y + 20 * sinf(fRadianAngle), -cosf(fRadianAngle), sinf(fRadianAngle), 10);
	pBullet->Initialize();
	dynamic_cast<CBullet*>(pBullet)->SetType(OBJECT_BULLET);

	return pBullet;
}

void CMonster::Move(float _ElapsedTime)
{
	m_Info.x += m_fSpeed * m_xDir * _ElapsedTime;
	m_Info.y += m_fSpeed * m_yDir * _ElapsedTime;

	if (m_Info.x > 250)
		m_xDir *= -1;
	else if (m_Info.x <= -250)
		m_xDir *= -1;


	if (m_Info.y > 250)
		m_yDir *= -1;
	else if (m_Info.y <= -250)
		m_yDir *= -1;

}



