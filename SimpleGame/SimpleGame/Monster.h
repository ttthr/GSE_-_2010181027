#pragma once
#include "GameObject.h"
#include "Bullet.h"
class CMonster :
	public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();
private:
	float  m_fSpeed;
	float  m_fLife;
	float  m_fAttack;
public:
	virtual void Initialize(void);
	virtual int Update(float _ElapsedTime);
private:
	list<CBullet*>* m_pBulletList;
	bool     m_bCheck;
public:
	void  SetBullet(list<CBullet*>* pBulletList);
	CBullet* CreateBullet(eDirType eType);
	float GetLife() { return m_fLife; }
	float GetMonsterAttack() { return m_fAttack; }
	void  MonsterLifeDown(float _fAttack) { m_fLife -= _fAttack; }


};

