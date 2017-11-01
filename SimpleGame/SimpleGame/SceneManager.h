#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "Renderer.h"
#include "GameTimer.h"
#include "Bullet.h"
#include "Buliding.h"
//
//#define	OBJECT_BUILDING = 1;
//#define	OBJECT_CHARACTER = 2;
//#define	OBJECT_BULLET = 3;
//#define	OBJECT_ARROW = 4;
//#define	OBJECT_END =5;


class CSceneManager
{

public:
	CSceneManager();
	~CSceneManager();
private:
	CBuliding* m_pBuliding = NULL;
	list<CBullet*>  m_pBullet;
	list<CMonster*> m_pMonster;
	Renderer* m_pRenderer = NULL;
	EnumList m_pEnum;
public:
	void AddBuliding(EnumList _type);
	void AddMonsterObject(float _x, float _y , EnumList _type);
	void ObjectUpdate(float _ElapsedTime);
	void ReleaseObject();
	void Render();
public: 
	//충돌 함수
 	void CollisionObject();
	//void CollisionPlayerMonster();
	void MonsterBulletColl();
	void BulidingMonsterColl();
	bool CollsionCheck(float _x, float _y, float _xSize, float _ySize, float _x1, float _y1, float _x1Size, float y1Size);
//렌더러 
public:
	Renderer* GetRenderer() { return m_pRenderer; }
public:
	CGameTimer* m_pGameTimer;
	CGameTimer* GetTimer() { return m_pGameTimer; }



};


