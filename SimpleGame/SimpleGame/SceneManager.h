#pragma once
#include "GameObject.h"
#include "Monster.h"
#include "Renderer.h"
#include "Bullet.h"
#include "Buliding.h"
#include "LoadPng.h"
#include "Buliding2.h"
#include "Monster2.h"

class CSceneManager
{

public:
	CSceneManager();
	~CSceneManager();
private:
	list<CGameObject*>  m_pGameObject[OBJECT_END];
	Renderer* m_pRenderer = NULL;
	GLuint m_TextureBuilding  = 0;
	GLuint m_TextureBuilding2 = 1;
	GLuint m_TextureBackGround = 2;
	GLuint m_CharaterTexture = 3;
	GLuint m_Charater1Texture = 4;
	GLuint m_Particle = 5;
	float  m_frameX = 0; 
	float  m_frameY = 0;
	float  m_frameMaxCountCharater1 = 17;
	float  m_frameMaxCountCharater2 = 8;
	float  m_fFrameTime = 0;
public:
	void AddActorObject(float _x, float _y, OBJECT_TYPE _type);
	void ObjectUpdate(float _ElapsedTime);
	void ReleaseObject();
	void Render();
public: 
	//충돌 함수
 	void CollisionObject();
	void BulletColl(OBJECT_TYPE _BulletType, OBJECT_TYPE _TargetType);
	void BulidingMonsterColl(OBJECT_TYPE _BulidingType, OBJECT_TYPE _MonsterType);
	bool CollsionCheck(float _x, float _y, float _xSize, float _ySize, float _x1, float _y1, float _x1Size, float y1Size);
public:
	//가운데 경계선을 그려주기 위해 렌더러를 갯한다
	Renderer* GetRenderer() { return m_pRenderer; }


};


