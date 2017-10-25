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
public:
	virtual void Initialize(void);
	virtual void Update(float _ElapsedTime);
	INFO GetInfo() { return m_Info; }
	virtual void SetInfo(INFO _Info);
	virtual void SetColor(float r, float g, float b, float a);
	virtual void SetPos(float _fx, float _fy);
	virtual void SetDir(float _xDir, float _yDir);
};

