#pragma once
#include "GameObject.h"

class CSceneManager
{

public:
	CSceneManager();
	~CSceneManager();
protected:
	INFO  m_Info;
public:
	virtual void Initialize(void);
	virtual void Update(void);
	INFO* GetInfo() { return &m_Info; }
	virtual void SetPos(float _fx, float _fy);
public:
	list<CGameObject*> m_pGameObject;

};


