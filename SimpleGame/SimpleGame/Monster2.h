#pragma once
#include "GameObject.h"
#include "Bullet.h"
class CMonster2 :
	public CGameObject
{
public:
	CMonster2();
	virtual ~CMonster2();
public:
	virtual void Initialize(void);
	virtual int  Update(float _ElapsedTime);
private:
	list<CGameObject*>* m_pBulletList;
	float               m_fBulletShotTime;
public:
	void  SetBullet(list<CGameObject*>* pBulletList);
	CGameObject* CreateBullet();
private:
	void Move(float _ElapsedTime);
};

