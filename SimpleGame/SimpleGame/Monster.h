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
public:
	virtual void Initialize(void);
	virtual int Update(float _ElapsedTime);


};

