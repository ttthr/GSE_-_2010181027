#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{	
	m_fLife = 30000;
	m_fAttack = 10;

}

CPlayer::~CPlayer()
{


}

void CPlayer::Initialize(void)
{
	m_Info.x = 150;
	m_Info.y = 150;
	m_Info.z = 0;
	m_Info.size = 40;
	m_Info.r = 0;
	m_Info.g = 0;
	m_Info.b = 0;
	m_Info.a = 0;

	m_bCheck = true;

}

int CPlayer::Update(float _ElapsedTime)
{

	if (m_Info.x > 250)
		m_Info.x = 250;
	else if (m_Info.x <= -250)
		m_Info.x = -250;

	if (m_Info.y > 250)
		m_Info.y = 250;
	else if (m_Info.y <= -250)
		m_Info.y = -250;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_Info.x -= 0.3f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_Info.x += 0.3f;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_Info.y += 0.3f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_Info.y -= 0.3f;

	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_bCheck)
	{
   		m_pBulletList->push_back(CreateBullet(DIR_DOWN));
		m_bCheck = false;
	}
	else if (!(GetAsyncKeyState(VK_SPACE) & 0x8000))
		m_bCheck = true;


  	return 0;
} 

void CPlayer::PlayerLifeDown(float _fAttack)
{
	m_fLife -= _fAttack;
}

void CPlayer::SetBullet(list<CGameObject*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

CGameObject *CPlayer::CreateBullet(eDirType eType)
{
	
	CGameObject* pBullet = new CBullet(m_Info.x, m_Info.y);
	pBullet->Initialize();
	dynamic_cast<CBullet*>(pBullet)->SetDir(eType);

	return pBullet;

}



