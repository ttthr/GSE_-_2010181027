#pragma once
#include "GameObject.h"
#include "Bullet.h"

class CBuliding2 :
	public CGameObject
{
public:
	CBuliding2();
	virtual ~CBuliding2();
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

