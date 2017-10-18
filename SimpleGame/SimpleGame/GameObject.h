#pragma once

class Renderer;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();
protected:
	INFO  m_Info;
public:
	virtual void Initialize(void);
	virtual void Update(void);
	INFO* GetInfo() { return &m_Info; }
	virtual void SetPos(float _fx, float _fy);
};

