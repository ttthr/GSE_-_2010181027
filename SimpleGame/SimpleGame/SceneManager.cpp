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

void CSceneManager::AddActorObject(float _x, float _y, OBJECT_TYPE _type)
{
	CGameObject* pGameObject{};

	switch (_type)
	{
	case OBJECT_BUILDING:
		pGameObject = new CBuliding();
		static_cast<CBuliding*>(pGameObject)->SetBullet(&m_pGameObject[OBJECT_BULLET]);
		break;
	case OBJECT_CHARACTER:
		pGameObject = new CMonster();
		static_cast<CMonster*>(pGameObject)->SetBullet(&m_pGameObject[OBJECT_BULLET]);
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
			int iResult = (*iter)->Update(_ElapsedTime);

			//리턴 값
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
		if (m_pGameObject[i].empty())
			continue;
		list<CGameObject*>::iterator iter = m_pGameObject[i].begin();
		list<CGameObject*>::iterator iter_end = m_pGameObject[i].end();

		for (iter; iter != iter_end; ++iter)
		{
			INFO Info = (*iter)->GetInfo();
			m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);
		}
	}

}

void CSceneManager::CollisionObject()
{


	list<CGameObject*>::iterator iter = m_pGameObject[OBJECT_CHARACTER].begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject[OBJECT_CHARACTER].end();

	for (iter; iter != iter_end; ++iter)
	{
		bool bCollCheck = false;

		list<CGameObject*>::iterator iter1 = m_pGameObject[OBJECT_CHARACTER].begin();
		list<CGameObject*>::iterator iter_end1 = m_pGameObject[OBJECT_CHARACTER].end();

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

void CSceneManager::BulletColl(OBJECT_TYPE _type)
{
	if (m_pGameObject[OBJECT_BULLET].empty() || m_pGameObject[_type].empty())
		return;

	list<CGameObject*>::iterator iterMonster = m_pGameObject[_type].begin();
	list<CGameObject*>::iterator iterMonster_end = m_pGameObject[_type].end();

	for (iterMonster; iterMonster != iterMonster_end; ++iterMonster)
	{
		list<CGameObject*>::iterator iter = m_pGameObject[OBJECT_BULLET].begin();

		for (iter; iter != m_pGameObject[OBJECT_BULLET].end(); )
		{
			INFO Bullet = (*iter)->GetInfo();
			INFO Monster = (*iterMonster)->GetInfo();

			if (CollsionCheck(Bullet.x, Bullet.y, Bullet.size, Bullet.size, Monster.x, Monster.y, Monster.size, Monster.size))
			{
				(*iterMonster)->DecreaseLife((*iter)->GetAttack());

				delete (*iter);
				iter = m_pGameObject[OBJECT_BULLET].erase(iter);
			}
			else
				++iter;
		}
	}
}

//void CSceneManager::CollisionMonsterBuliding()
//{
//	//빌딩 객체 
//
//	if (m_pBuliding != NULL)
//	{
//
//			//몬스터 객체
//			list<CMonster*>::iterator iterAnother = m_pMonster.begin();
//			list<CMonster*>::iterator iterAnother_end = m_pMonster.end();
//
//			//충돌할 두 객체정보를 받는다.
//			INFO Monster = (*iterAnother)->GetInfo();
//
//			if (CollsionCheck(m_pBuliding->GetInfo().x, m_pBuliding->GetInfo().y, m_pBuliding->GetInfo().size, m_pBuliding->GetInfo().size, Monster.x, Monster.y, Monster.size, Monster.size))
//			{
//				//충돌하면 빨간색
//				(*iterAnother)->SetColor(255, 0, 0, 255);
//				m_pBuliding->SetColor(255, 0, 0, 255);
//			}
//			else
//			{
//				//아니면 흰색
//				(*iterAnother)->SetColor(255, 255, 255, 255);
//				m_pBuliding->SetColor(255, 255, 0, 255);
//			}
//
//		}
//
//
//
//}


//void CSceneManager::BulidingMonsterColl()
//{
//	
//	
//		list<CGameObject*>::iterator iter     = m_pMonster.begin();
//		list<CGameObject*>::iterator iter_end = m_pMonster.end();
//
//						
//		if (!m_pMonster.empty())
//		{
//			for (iter; iter != iter_end; ++iter)
//			{
//
//				INFO Monster = (*iter)->GetInfo();
//
//			
//					if (CollsionCheck(m_pBuliding->GetInfo().x, m_pBuliding->GetInfo().y, m_pBuliding->GetInfo().size, m_pBuliding->GetInfo().size, Monster.x, Monster.y, Monster.size, Monster.size))
//					{
//						{
//							m_pBuliding->BulidingLifeDown(((CMonster*)(*iter))->GetMonsterAttack());
//
//							if (m_pBuliding->GetLife() <= 0)
//							{
//								delete m_pBuliding;
//								//m_pBuliding = NULL;
//							}
//						}
//					}
//				
//			
//			}
//
//		}
//	}
//

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
