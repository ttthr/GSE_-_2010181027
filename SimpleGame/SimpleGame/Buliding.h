#pragma once
#include "GameObject.h"
#include "Bullet.h"

class CBuliding :
	public CGameObject
{
public:
	CBuliding();
	virtual ~CBuliding();
public:
	virtual void  Initialize(void);
	virtual int   Update(float _ElapsedTime);
private:
	list<CGameObject*>* m_pBulletList;
	float               m_fBulletShotTime;
public:
	void  SetBullet(list<CGameObject*>* pBulletList);
	CGameObject* CreateBullet();
};

