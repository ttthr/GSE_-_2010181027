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
	m_Info.y = 150;
	m_Info.size = 80;

}

int CBuliding::Update(float _ElapsedTime)
{
	
	

	return 0;
}

void CBuliding::SetBullet(list<CGameObject*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

CGameObject * CBuliding::CreateBullet(eDirType eType)
{
	
	CGameObject* pBullet = new CBullet(m_Info.x, m_Info.y);
	pBullet->Initialize();
	dynamic_cast<CBullet*>(pBullet)->SetDir(eType);

	return pBullet;

}
