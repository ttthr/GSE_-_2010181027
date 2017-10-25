#pragma once
#include "GameObject.h"
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
	virtual void Update(void);
	float GetMonsterLife() { return m_fLife; }
	void SetMonsterLife(float _fLife);

};

