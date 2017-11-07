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
	float m_fSpeed;
	float m_fLife;
	float m_fAttack;
	float m_fLifeTime = 500;
public:
	virtual void  Initialize(void);
	virtual int   Update(float _ElapsedTime);
    INFO  GetInfo() { return m_Info; }
	void  SetInfo(INFO _Info);
	void  SetColor(float r, float g, float b, float a);
	void  SetPos(float _fx, float _fy);
	void  SetDir(float _xDir, float _yDir);
	void  DecreaseLife(float _fAttack) { m_fLife -= _fAttack; }
	float GetAttack() { return m_fAttack; }
	void  DecreaseLifeTime(float _fLifeTime) { m_fLifeTime -= _fLifeTime; }
	float GetLifeTime() { return m_fLifeTime; }
};

