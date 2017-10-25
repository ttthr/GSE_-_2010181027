#include "stdafx.h"
#include "SceneManager.h"


CSceneManager::CSceneManager()
{


	m_pRenderer = new Renderer(500, 500);


	if (!m_pRenderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

}


CSceneManager::~CSceneManager()
{
	ReleaseObject();
	if (m_pRenderer)
	{
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
		
}
void CSceneManager::AddgameObject(INFO _Info)
{
	CGameObject* pObject = new CGameObject();

	pObject->SetInfo(_Info);

	m_pGameObject.push_back(pObject);



}
void CSceneManager::AddgamePlayerObject(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a)
{
	CGameObject* pObject = new CPlayer();
	pObject->SetInfo(INFO{ _x,  _y , _z, _size, _r, _g, _b, _a });


	m_pGameObject.push_back(pObject);



}
void CSceneManager::AddMonstergameObject(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a)
{
	CGameObject* pObject = new CMonster();
	pObject->SetInfo(INFO{ _x,  _y , _z, _size, _r, _g, _b, _a });

	// 몬스터들 자동으로 이동 
	// 랜덤한 방향 설정
	int randx;
	int randy;
	while (1)
	{
		randx = rand() % 3 - 1;
		randy = rand() % 3 - 1;


		if (randx == 0 && randy == 0)
			continue;
		else
			break;
	}
	pObject->SetDir(randx, randy);

	m_pGameObject.push_back(pObject);

	
}
void CSceneManager::ObjectUpdate()
{


	list<CGameObject*>::iterator iter_player = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_playerend = m_pGameObject.end();

	for (iter_player; iter_player != iter_playerend; ++iter_player)
	{
		((CPlayer*)(*iter_player))->Update();
	}

	//몬스터 생성
	list<CGameObject*>::iterator iter_monster = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_monsterend = m_pGameObject.end();

	for (iter_monster; iter_monster != iter_monsterend; ++iter_monster)
	{
		((CMonster*)(*iter_monster))->Update();
	}

}
void CSceneManager::ReleaseObject()
{
	list<CGameObject*>::iterator iter     = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject.end();

	for (iter; iter != iter_end; ++iter)
	{
		delete (*iter);

		iter = m_pGameObject.erase(iter);
	}

}

void CSceneManager::CollisionObject()
{

	//몬스터 객체
	list<CGameObject*>::iterator iterAnother = m_pGameObject.begin();
	list<CGameObject*>::iterator iterAnother_end = m_pGameObject.end();

	auto iter_player = m_pGameObject.begin(); //플레이어
	iterAnother++;

	for (iterAnother; iterAnother != iterAnother_end; ++iterAnother)
	{

		//충돌할 두 객체정보를 받는다.
		INFO Player = ((CPlayer*)(*iter_player))->GetInfo();
		INFO Monster = ((CMonster*)(*iterAnother))->GetInfo();

		if (CollsionCheck(Player.x, Player.y, Player.size, Player.size, Monster.x, Monster.y, Monster.size, Monster.size))
		{
			//충돌하면 빨간색
			((CMonster*)(*iterAnother))->SetColor(255, 0, 0, 255);
		}
		else
		{
			//아니면 흰색
			((CMonster*)(*iterAnother))->SetColor(255, 255, 255, 255);
		}
	}

}

bool CSceneManager::CollsionCheck(float _x, float _y, float _xSize, float _ySize, float _x1, float _y1, float _x1Size, float y1Size)
{
	// API 렉트  충돌 함수 내부를 비슷하게 구현
	float leftPlayer = _x - _xSize / 2;
	float rightPlayer = _x + _xSize / 2;
	float topPlayer = _y + _ySize / 2;
	float bottomPlayer = _y - _ySize / 2;
	float leftmonster = _x1 - _x1Size / 2;
	float rightmonster = _x1 + _x1Size / 2;
	float topmonster = _y1 - y1Size / 2;
	float bottommonster = _y1 - y1Size / 2;


	if (leftPlayer > rightmonster) return false;
	if (rightPlayer < leftmonster) return false;
	if (topPlayer < bottommonster) return false;
	if (bottomPlayer > topmonster) return false;

	return true;
}
