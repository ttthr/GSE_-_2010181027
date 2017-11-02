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

	m_bCheck = true;

	m_fLife = 500;

}

int CBuliding::Update(float _ElapsedTime)
{
	
	//if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_bCheck)
	//{
	//	m_pBulletList->push_back(CreateBullet(DIR_DOWN));
	//	m_bCheck = false;
	//}
	//else if (!(GetAsyncKeyState(VK_SPACE) & 0x8000))
	//	m_bCheck = true;
	m_fBulletShotTime += 1;

	if (m_fBulletShotTime >= 3.f)
	{
		m_pBulletList->push_back(CreateBullet(DIR_DOWN));
		m_pBulletList->push_back(CreateBullet(DIR_LEFT));
		m_pBulletList->push_back(CreateBullet(DIR_RIGHT));
		m_pBulletList->push_back(CreateBullet(DIR_UP_L));
		m_pBulletList->push_back(CreateBullet(DIR_UP_R));
		m_pBulletList->push_back(CreateBullet(DIR_UP));
		m_pBulletList->push_back(CreateBullet(DIR_DOWN_L));
		m_pBulletList->push_back(CreateBullet(DIR_DOWN_R));
	}

	m_fBulletShotTime = 0;

	//if (0 < _ElapsedTime < 30 && m_bCheck)
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

void CBuliding::SetBullet(list<CGameObject*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

CGameObject* CBuliding::CreateBullet(eDirType eType)
{

	CGameObject *pBullet = new CBullet(m_Info.x, m_Info.y);
	pBullet->Initialize();
	dynamic_cast<CBullet*>(pBullet)->SetDir(eType);
	dynamic_cast<CBullet*>(pBullet)->SetType(OBJECT_ARROW);

	return pBullet;

}
