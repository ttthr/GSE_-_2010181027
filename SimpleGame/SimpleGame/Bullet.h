#pragma once
#include "GameObject.h"
class CBullet :
	public CGameObject
{
public:
	CBullet();
	virtual ~CBullet();

virtual void Initialize(void);
virtual void Update(float _ElapsedTime);
};

