#pragma once

class Renderer;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();
protected:
	INFO  m_Info;
	float m_xDir;
	float m_yDir;
	float m_fspeed;
	float m_fLife;
	float m_fLifeTime;
	float m_fAttack;
public:
	virtual void Initialize(void);
	virtual int Update(float _ElapsedTime);
	INFO GetInfo() { return m_Info; }
	virtual void SetInfo(INFO _Info);
	virtual void SetColor(float r, float g, float b, float a);
	virtual void SetPos(float _fx, float _fy);
	virtual void SetDir(float _xDir, float _yDir);
	float GetMonsterLifeTime() { return m_fLifeTime; }
	void  DecreaseLife(float _fTime) { m_fLifeTime -= _fTime; }
	float GetMonsterLife() { return m_fLife; }
	void  MonsterLifeDown(float _fAttack) { m_fLife -= _fAttack; }
};

