#pragma once
#include "GameObject.h"
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
public:
	virtual void Initialize(void);
	virtual void Update(float _ElapsedTime);
	float GetPlayerLife() { return m_fLife; }
	void  PlayerLifeDown(float _fAttack);
	float PlayerAttack() { return m_fAttack; }

};

