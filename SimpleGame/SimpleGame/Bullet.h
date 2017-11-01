#pragma once
#include "GameObject.h"
class CBullet :
	public CGameObject
{
public:
	CBullet();
	CBullet(float _PlayerPosX, float _PlayerPosY);
	virtual ~CBullet();

	virtual void Initialize(void);
	virtual int Update(float _ElapsedTime);
private:
	eDirType  m_eType;
	float     m_fSpeed;
public:
	inline void SetDir(eDirType eType)
	{
		m_eType = eType;
	}

};

