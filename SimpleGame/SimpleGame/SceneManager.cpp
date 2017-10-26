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
void CSceneManager::AddgameObject(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a)
{
	CGameObject* pObject = new CGameObject();
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
void CSceneManager::ObjectUpdate(float _ElapsedTime)
{

	//오브젝트 업데이트
	list<CGameObject*>::iterator iter    = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end= m_pGameObject.end();

	for (; iter != iter_end;)
	{
		(*iter)->Update(_ElapsedTime);
		(*iter)->DecreaseLife(1);

		if ((*iter)->GetMonsterLifeTime() <= 0)
		{
			delete (*iter);
			iter = m_pGameObject.erase(iter);
		}
		else
			iter++;
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

	
	list<CGameObject*>::iterator iter = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject.end();

	for (iter; iter != iter_end;++iter)
	{
		bool bCollCheck = false;

		list<CGameObject*>::iterator iter1 = m_pGameObject.begin();
		list<CGameObject*>::iterator iter_end1 = m_pGameObject.end();

		for (iter1; iter1 != iter_end1; ++iter1)
		{
			if (*iter == *iter1)
				continue;

			INFO monster  = (*iter)->GetInfo();
			INFO monster1 = (*iter1)->GetInfo();

			if (CollsionCheck(monster.x, monster.y, monster.size, monster.size, monster1.x, monster1.y, monster1.size, monster1.size))
			{
				//불값으로 무언가 충돌되었다고 판단 시킴
				bCollCheck = true;
				break;
			}
	
		}
	
		if (bCollCheck == true)
		{
			//충돌되었으면 빨강
			(*iter)->SetColor(255, 0, 0, 255);
		}
		else
		{ 
			//아니라면 흰색
			(*iter)->SetColor(255, 255, 255, 0);
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
	float topmonster = _y1 + y1Size / 2;
	float bottommonster = _y1 - y1Size / 2;


	if (leftPlayer > rightmonster) return false;
	if (rightPlayer < leftmonster) return false;
	if (topPlayer < bottommonster) return false;
	if (bottomPlayer > topmonster) return false;

	return true;
}
