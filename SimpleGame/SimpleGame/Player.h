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
public:
	virtual void Initialize(void);
	virtual void Update(void);

};

