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

	m_bCheck = true;

	m_fAttack = 50;

}

int  CMonster::Update(float _ElapsedTime)
{
	//타임 매니저 같은 역할을 하기 위한 변수 
	//float ElapsedTime = 0.1;


	m_Info.x += m_fspeed * m_xDir * _ElapsedTime;
	m_Info.y += m_fspeed * m_yDir * _ElapsedTime;

	if (m_Info.x > 250)
		m_xDir *= -1;
	else if (m_Info.x <= -250)
		m_xDir *= -1;


	if (m_Info.y > 250)
		m_yDir *= -1;
	else if (m_Info.y <= -250)
		m_yDir *= -1;

		//if (0 < _ElapsedTime < 10 && m_bCheck)
		//{
		//	m_pBulletList->push_back(CreateBullet(DIR_DOWN));
		//	m_pBulletList->push_back(CreateBullet(DIR_LEFT));
		//	m_pBulletList->push_back(CreateBullet(DIR_RIGHT));
		//	m_pBulletList->push_back(CreateBullet(DIR_UP_L));
		//	m_pBulletList->push_back(CreateBullet(DIR_UP_R));
		//	m_pBulletList->push_back(CreateBullet(DIR_UP));
		//	m_pBulletList->push_back(CreateBullet(DIR_DOWN_L));
		//	m_pBulletList->push_back(CreateBullet(DIR_DOWN_R));
		//	m_bCheck = false;
		//}
	

	return 0;
}

void CMonster::SetBullet(list<CBullet*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

CBullet * CMonster::CreateBullet(eDirType eType)
{
	CBullet *pBullet = new CBullet(m_Info.x , m_Info.y);
	pBullet->Initialize();
	dynamic_cast<CBullet*>(pBullet)->SetDir(eType);
	dynamic_cast<CBullet*>(pBullet)->SetType(OBJECT_BULLET);
	return pBullet;
}



