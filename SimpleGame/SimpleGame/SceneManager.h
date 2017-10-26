#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "Renderer.h"
#include "GameTimer.h"

class CSceneManager
{

public:
	CSceneManager();
	~CSceneManager();
private:
	list<CGameObject*> m_pGameObject;
	Renderer* m_pRenderer = NULL;
public:
	list<CGameObject*>* GetgameObject() { return &m_pGameObject; }
	void AddgameObject(INFO _Info);
	void AddgameObject(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a);
	void ObjectUpdate(float _ElapsedTime);
	void ReleaseObject();
public: 
	//충돌 함수
 	void CollisionObject();
	bool CollsionCheck(float _x, float _y, float _xSize, float _ySize, float _x1, float _y1, float _x1Size, float y1Size);
//렌더러 
public:
	Renderer* GetRenderer() { return m_pRenderer; }
public:
	CGameTimer* m_pGameTimer;
	CGameTimer* GetTimer() { return m_pGameTimer; }



};


