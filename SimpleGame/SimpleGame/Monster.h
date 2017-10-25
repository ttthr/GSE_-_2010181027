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
	virtual void Update(float _ElapsedTime);
	float GetMonsterLife() { return m_fLife; }
	void SetMonsterLife(float _fLife);

};

