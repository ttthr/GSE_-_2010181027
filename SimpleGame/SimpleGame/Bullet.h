#pragma once
#include "GameObject.h"

enum Bullet
{
	
};
class CBullet :
	public CGameObject
{
public:
	CBullet();
	CBullet(float _PosX, float _PosY , float _DirX , float _DirY , float fAttack );
	virtual ~CBullet();

	virtual void Initialize(void);
	virtual int  Update(float _ElapsedTime);
private:
	OBJECT_TYPE  m_eBulletType;
public:
	inline void SetType(OBJECT_TYPE bType)
	{
		m_eBulletType = bType;

		switch (m_eBulletType)
		{
		case OBJECT_BULLET:
			m_Info.r = 255;
			m_Info.g = 0;
			m_Info.b = 0;
			m_Info.a = 255;
			break;
		case OBJECT_ARROW:
			m_Info.r = 0;
			m_Info.g = 150;
			m_Info.b = 255;
			m_Info.a = 255;
			break;
		}
	}
public:
	void Move(float _ElapsedTime);
};

