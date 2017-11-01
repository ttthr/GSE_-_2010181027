#pragma once
#include "GameObject.h"
#include "Bullet.h"

class CPlayer :
	public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();
private:
	float  m_fSpeed;
	float  m_fLife;
	float  m_fAttack;
	list<CGameObject*>* m_pBulletList;
	eDirType m_eDir;
	bool     m_bCheck;
public:
	virtual void Initialize(void);
	virtual int  Update(float _ElapsedTime);
	float GetPlayerLife() { return m_fLife; }
	void  PlayerLifeDown(float _fAttack);
	float PlayerAttack() { return m_fAttack; }
	void  SetBullet(list<CGameObject*>* pBulletList);
	CGameObject* CreateBullet(eDirType eType);

};

