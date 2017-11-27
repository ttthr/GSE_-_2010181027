#include "stdafx.h"
#include "SceneManager.h"
#include "Bullet.h"

CSceneManager::CSceneManager()
{

	m_pRenderer = new Renderer(500, 800);

	if (!m_pRenderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	m_TextureBuilding = m_pRenderer->CreatePngTexture("../../Resource/BuildingTexture.png");
	m_TextureBuilding2 = m_pRenderer->CreatePngTexture("../../Resource/BuildingTexture2.png");
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

void CSceneManager::AddActorObject(float _x, float _y, OBJECT_TYPE _type)
{
	CGameObject* pGameObject{};

	switch (_type)
	{
	case OBJECT_TEAM1:
		pGameObject = new CBuliding();
		static_cast<CBuliding*>(pGameObject)->SetBullet(&m_pGameObject[OBJECT_ARROW_TEAM1]);
		break;
	case OBJECT_TEAM2:
		pGameObject = new CBuliding2();
		static_cast<CBuliding2*>(pGameObject)->SetBullet(&m_pGameObject[OBJECT_ARROW_TEAM2]);
		break;
	case OBJECT_CHARACTER_TEAM1:
		pGameObject = new CMonster();
		static_cast<CMonster*>(pGameObject)->SetBullet(&m_pGameObject[OBJECT_BULLET_TEAM1]);
		break;
	case OBJECT_CHARACTER_TEAM2:
		pGameObject = new CMonster2();
		static_cast<CMonster*>(pGameObject)->SetBullet(&m_pGameObject[OBJECT_BULLET_TEAM2]);
		break;
	default:
		return;
	}

	//공통 생성
	pGameObject->Initialize();
	pGameObject->SetPos(_x, _y);

	m_pGameObject[_type].push_back(pGameObject);

}

void CSceneManager::ObjectUpdate(float _ElapsedTime)
{

	for (int i = 0; i < OBJECT_END; ++i)
	{
		if (m_pGameObject[i].empty())
			continue;

		// 공통 업데이트
		list<CGameObject*>::iterator iter = m_pGameObject[i].begin();

		for (iter; iter != m_pGameObject[i].end();)
		{
			//총알과 빌딩의 라이프타임은 10000.f 이고 
			// 매 프레임 0.1씩 달게해서 시간이 다되면 return 1타서 삭제
			(*iter)->DecreaseLifeTime(0.1f);
			//각각 객체의 업데이트 결과를 담는다.
			int iResult = (*iter)->Update(_ElapsedTime);

			//리턴 값으로 삭제처리
			if (iResult & 1)
			{
				delete (*iter);
				iter = m_pGameObject[i].erase(iter);
			}
			else
			{
				++iter;
			}

		}

	}
}


void CSceneManager::ReleaseObject()
{


	for (int i = 0; i < OBJECT_END; ++i)
	{

		if (m_pGameObject[i].empty())
			continue;
		list<CGameObject*>::iterator iter = m_pGameObject[i].begin();

		for (iter; iter != m_pGameObject[i].end();)
		{

			delete (*iter);
			iter = m_pGameObject[i].erase(iter);

		}

	}

	//for (int i = 0; i < OBJECT_END; ++i)
	//{
	//	if (m_pGameObject[i].empty())
	//		continue;

	//	list<CGameObject*>::iterator iter = m_pGameObject[i].begin();
	//	list<CGameObject*>::iterator iter_end = m_pGameObject[i].end();

	//	for (iter; iter != iter_end; ++iter)
	//		delete (*iter);

	//	iter = m_pGameObject[i].begin();
	//	m_pGameObject[i].erase(iter, iter_end);
	//}

}

void CSceneManager::Render()
{

	for (int i = 0; i < OBJECT_END; ++i)
	{
		list<CGameObject*>::iterator iter = m_pGameObject[i].begin();
		list<CGameObject*>::iterator iter_end = m_pGameObject[i].end();

		for (iter; iter != iter_end; ++iter)
		{
			INFO Info = (*iter)->GetInfo();

			if (i == OBJECT_TEAM1)
			{
				m_pRenderer->DrawTexturedRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a, m_TextureBuilding, 0.1);
				m_pRenderer->DrawSolidRectGauge(Info.x, Info.y + 50, Info.z, 80, 10, 255, 0, 0, 255, (*iter)->GetLife() / (*iter)->GetMaxLife(), 0.1);
				m_pRenderer->DrawSolidRectGauge(Info.x, Info.y + 50, Info.z, 80, 10, 255, 0, 0, 255, (*iter)->GetLife() / (*iter)->GetMaxLife(), 0.1);
				m_pRenderer->DrawSolidRectGauge(Info.x, Info.y + 50, Info.z, 80, 10, 255, 0, 0, 255, (*iter)->GetLife() / (*iter)->GetMaxLife(), 0.1);
			}
			else if (i == OBJECT_TEAM2)
			{
				m_pRenderer->DrawTexturedRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a, m_TextureBuilding2, 0.1);
				m_pRenderer->DrawSolidRectGauge(Info.x, Info.y + 50, Info.z, 80, 10, 0, 0, 255, 255, (*iter)->GetLife() / (*iter)->GetMaxLife(), 0.1);
			}
			else if (i == OBJECT_CHARACTER_TEAM1)
			{
				m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a, 0.2);
				m_pRenderer->DrawSolidRectGauge(Info.x, Info.y + 20, Info.z, 20, 6, Info.r, Info.g, Info.b, Info.a, (*iter)->GetLife() / (*iter)->GetMaxLife(), 0.2);
			}
			else if (i == OBJECT_CHARACTER_TEAM2)
			{
				m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a, 0.2);
				m_pRenderer->DrawSolidRectGauge(Info.x, Info.y + 20, Info.z, 20, 6, Info.r, Info.g, Info.b, Info.a, (*iter)->GetLife() / (*iter)->GetMaxLife(), 0.2);
			}
			else if (i == OBJECT_ARROW_TEAM1)
			{
				m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a, 0.3);
			}
			else if (i == OBJECT_ARROW_TEAM2)
			{
				m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a, 0.3);
			}
			else if (i == OBJECT_BULLET_TEAM1)
			{
				m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a, 0.3);
			}
			else if (i == OBJECT_BULLET_TEAM2)
			{
				m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a, 0.3);
			}


		}
	}

}

void CSceneManager::CollisionObject()
{

	list<CGameObject*>::iterator iter = m_pGameObject[OBJECT_BULLET_TEAM1].begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject[OBJECT_BULLET_TEAM1].end();

	for (iter; iter != iter_end; ++iter)
	{
		bool bCollCheck = false;

		list<CGameObject*>::iterator iter1 = m_pGameObject[OBJECT_BULLET_TEAM1].begin();
		list<CGameObject*>::iterator iter_end1 = m_pGameObject[OBJECT_BULLET_TEAM1].end();

		for (iter1; iter1 != iter_end1; ++iter1)
		{
			if ((*iter) == (*iter1))
				continue;

			INFO monster = (*iter)->GetInfo();
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

void CSceneManager::BulletColl(OBJECT_TYPE _BulletType, OBJECT_TYPE _TargetType)
{
	if (m_pGameObject[_BulletType].empty() || m_pGameObject[_TargetType].empty())
		return;

	list<CGameObject*>::iterator iterTarget = m_pGameObject[_TargetType].begin();
	list<CGameObject*>::iterator iterTarget_end = m_pGameObject[_TargetType].end();

	for (iterTarget; iterTarget != iterTarget_end; ++iterTarget)
	{

		list<CGameObject*>::iterator iter = m_pGameObject[_BulletType].begin();

		for (iter; iter != m_pGameObject[_BulletType].end(); ++iter)
		{
			INFO Bullet = (*iter)->GetInfo();
			INFO Target = (*iterTarget)->GetInfo();

			

			if (CollsionCheck(Bullet.x, Bullet.y, Bullet.size, Bullet.size, Target.x, Target.y, Target.size, Target.size))
			{

				(*iterTarget)->DecreaseLife((*iter)->GetAttack());
				
				(*iter)->SetDeadCheck();

				if ((*iterTarget)->GetLife() <= 0)
				{
					(*iterTarget)->SetDeadCheck();
				}


			}

		}
	}
}

void CSceneManager::BulidingMonsterColl(OBJECT_TYPE _BulidingType, OBJECT_TYPE _MonsterType)
{
	if (m_pGameObject[_MonsterType].empty())
		return;


	list<CGameObject*>::iterator iterMonster = m_pGameObject[_MonsterType].begin();
	list<CGameObject*>::iterator iterMonster_end = m_pGameObject[_MonsterType].end();

	for (iterMonster; iterMonster != iterMonster_end; ++iterMonster)
	{
		list<CGameObject*>::iterator iter = m_pGameObject[_BulidingType].begin();

		for (iter; iter != m_pGameObject[_BulidingType].end(); ++iter)
		{
			INFO Buliding = (*iter)->GetInfo();
			INFO Monster  = (*iterMonster)->GetInfo();

			if (!m_pGameObject[_BulidingType].empty())
			{
				if (CollsionCheck(Buliding.x, Buliding.y, Buliding.size, Buliding.size, Monster.x, Monster.y, Monster.size, Monster.size))
				{
					(*iter)->DecreaseLife((*iterMonster)->GetAttack());
					(*iterMonster)->DecreaseLife((*iter)->GetAttack());
				
					if ((*iter)->GetLife() <= 0)
					{
						(*iter)->SetDeadCheck();
					}
					else if ((*iterMonster)->GetLife() <= 0)
					{

						(*iterMonster)->SetDeadCheck();
					}

				}

			}

		}
	}

}

bool CSceneManager::CollsionCheck(float _x, float _y, float _xSize, float _ySize, float _x1, float _y1, float _x1Size, float y1Size)
{
	// API 렉트  충돌 함수 내부를 비슷하게 구현
	float leftPlayer = _x - _xSize / 2;
	float rightPlayer = _x + _xSize / 2;
	float tom_pPlayer = _y + _ySize / 2;
	float bottomPlayer = _y - _ySize / 2;
	float leftmonster = _x1 - _x1Size / 2;
	float rightmonster = _x1 + _x1Size / 2;
	float topmonster = _y1 + y1Size / 2;
	float bottommonster = _y1 - y1Size / 2;


	if (leftPlayer > rightmonster) return false;
	if (rightPlayer < leftmonster) return false;
	if (tom_pPlayer < bottommonster) return false;
	if (bottomPlayer > topmonster) return false;

	return true;
}
