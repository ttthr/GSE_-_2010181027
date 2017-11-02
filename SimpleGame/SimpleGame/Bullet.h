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
	CBullet(float _PosX, float _PosY);
	virtual ~CBullet();

	virtual void Initialize(void);
	virtual int Update(float _ElapsedTime);
private:
	eDirType  m_eType;
	float     m_fSpeed;
	float     m_fAttack;
	BulletType m_eBulletType;
public:
	inline void SetDir(eDirType eType)
	{
		m_eType = eType;
	}
	inline void SetType(BulletType bType)
	{
		m_eBulletType = bType;
	}
public:
	void Dir();
	void Type();
	float GetAttack() { return m_fAttack; }


};

