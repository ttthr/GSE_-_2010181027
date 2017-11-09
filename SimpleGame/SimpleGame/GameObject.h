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
	bool  m_bDeadCheck;
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
	float GetLife() { return m_fLife; }
	bool GetDeadCheck(void) { return m_bDeadCheck;}
	void SetDeadCheck(bool _DeadType = true){ m_bDeadCheck = _DeadType; }
};

