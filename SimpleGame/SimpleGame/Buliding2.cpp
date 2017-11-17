#include "stdafx.h"
#include "Buliding2.h"


CBuliding2::CBuliding2()
{
}


CBuliding2::~CBuliding2()
{
}

void CBuliding2::Initialize(void)
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
	m_fBulletShotTime = 1.f;
	m_fAttack = 30.f;
	m_fLifeTime = 1000.f;
}

int CBuliding2::Update(float _ElapsedTime)
{
	//����üũ
	if (m_bDeadCheck == true)
		return 1;

	//3�ʸ��� ���
	m_fBulletShotTime -= _ElapsedTime;

	//�ð� ������ ��ü ����
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

void CBuliding2::SetBullet(list<CGameObject*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

CGameObject * CBuliding2::CreateBullet()
{
	float fRadianAngle = float(rand() % 360) / 180 * 3.141592f;

	CGameObject *pBullet = new CBullet(m_Info.x + 57 * -cosf(fRadianAngle), m_Info.y + 57 * sinf(fRadianAngle), -cosf(fRadianAngle), sinf(fRadianAngle), 20 , 100, 10);
	pBullet->Initialize();
	dynamic_cast<CBullet*>(pBullet)->SetType(OBJECT_ARROW_TEAM2);

	return pBullet;
}
