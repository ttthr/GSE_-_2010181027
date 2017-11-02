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
void CSceneManager::AddBuliding(EnumList _type)
{
	
	m_pBuliding = new CBuliding();
	m_pBuliding->Initialize();
	m_pBuliding->SetInfo(INFO{ m_pBuliding->GetInfo().x, m_pBuliding->GetInfo().y , m_pBuliding->GetInfo().z ,m_pBuliding->GetInfo().size, m_pBuliding->GetInfo().r, m_pBuliding->GetInfo().g, m_pBuliding->GetInfo().b, m_pBuliding->GetInfo().a });
	m_pBuliding->SetBullet(&m_pBullet);

}

void CSceneManager::AddMonsterObject(float _x, float _y, EnumList _type)
{

	CGameObject* pObject = new CMonster();
	pObject->Initialize();
	pObject->SetInfo(INFO{ _x,  _y , pObject->GetInfo().z ,pObject->GetInfo().size, pObject->GetInfo().r, pObject->GetInfo().g, pObject->GetInfo().b, pObject->GetInfo().a });
	((CMonster*)pObject)->SetBullet(&m_pBullet);
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

	m_pMonster.push_back(pObject);


}

void CSceneManager::ObjectUpdate(float _ElapsedTime)
{

	//불렛 업데이트
	list<CGameObject*>::iterator iterBullet = m_pBullet.begin();
	list<CGameObject*>::iterator iterBullet_end = m_pBullet.end();

	for (iterBullet; iterBullet != iterBullet_end; ++iterBullet)
	{
		((CBullet*)(*iterBullet))->Update(_ElapsedTime);

	}

	//몬스터 오브젝트 업데이트

	list<CGameObject*>::iterator iterMonster     =  m_pMonster.begin();
	list<CGameObject*>::iterator iter_Monsterend =  m_pMonster.end();

	for (iterMonster; iterMonster != iter_Monsterend; ++iterMonster)
	{
		((CMonster*)(*iterMonster))->Update(_ElapsedTime);
	}

	//빌딩 업데이트
	m_pBuliding->Update(_ElapsedTime);

}

void CSceneManager::ReleaseObject()
{
	list<CGameObject*>::iterator iter     = m_pMonster.begin();
	list<CGameObject*>::iterator iter_end = m_pMonster.end();

	for (iter; iter != iter_end; ++iter)
	{
		delete (*iter);
		iter = m_pMonster.erase(iter);
	}

}

void CSceneManager::Render()
{

	//불렛 랜더
	list<CGameObject*>::iterator iterBullet     = m_pBullet.begin();
	list<CGameObject*>::iterator iterBullet_end = m_pBullet.end();

	for (iterBullet; iterBullet != iterBullet_end; ++iterBullet)
	{
		INFO Info = ((CBullet*)(*iterBullet))->GetInfo();

		m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);
	}

	//몬스터 랜더
	list<CGameObject*>::iterator iterMonster     = m_pMonster.begin();
	list<CGameObject*>::iterator iter_Monsterend = m_pMonster.end();

	for (iterMonster; iterMonster != iter_Monsterend; ++iterMonster)
	{
		INFO Info = ((CMonster*)(*iterMonster))->GetInfo();

		m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);

	}

	//빌딩 랜더
	m_pRenderer->DrawSolidRect(m_pBuliding->GetInfo().x, m_pBuliding->GetInfo().y, m_pBuliding->GetInfo().z, m_pBuliding->GetInfo().size, m_pBuliding->GetInfo().r, m_pBuliding->GetInfo().g, m_pBuliding->GetInfo().b, m_pBuliding->GetInfo().a);


}

void CSceneManager::CollisionObject()
{

	
	list<CGameObject*>::iterator iter     = m_pMonster.begin();
	list<CGameObject*>::iterator iter_end = m_pMonster.end();

	for (iter; iter != iter_end;++iter)
	{
		bool bCollCheck = false;

		list<CGameObject*>::iterator iter1     = m_pMonster.begin();
		list<CGameObject*>::iterator iter_end1 = m_pMonster.end();

		for (iter1; iter1 != iter_end1; ++iter1)
		{
			if ((*iter) == (*iter1))
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

void CSceneManager::MonsterBulletColl()
{
	list<CGameObject*>::iterator iter     = m_pBullet.begin();
	list<CGameObject*>::iterator iter_end = m_pBullet.end();

	if (!m_pBullet.empty())
	{
		for (iter ; iter != iter_end; ++iter)
		{
			if (!m_pMonster.empty())
			{
				list<CGameObject*>::iterator iter1     = m_pMonster.begin();
				list<CGameObject*>::iterator iter_end1 = m_pMonster.end();

				for (iter1 ; iter1 != iter_end1; ++iter1)
				{
					INFO Bullet = ((CBullet*)*iter)->GetInfo();
					INFO Monster = ((CMonster*)*iter1)->GetInfo();

					if (CollsionCheck(Bullet.x, Bullet.y, Bullet.size, Bullet.size, Monster.x, Monster.y, Monster.size, Monster.size))
					{
						
						((CMonster*)*iter1)->MonsterLifeDown(((CBullet*)*iter)->GetAttack());

						delete (*iter);
						iter = m_pBullet.erase(iter);

						if (((CMonster*)*iter1)->GetLife() <= 0)
						{
							delete (*iter1);
							iter1 = m_pMonster.erase(iter1);
						}
					
						return;
				
					}

				}
			}
		}

	}
}

void CSceneManager::BulidingMonsterColl()
{
	
	
		list<CGameObject*>::iterator iter     = m_pMonster.begin();
		list<CGameObject*>::iterator iter_end = m_pMonster.end();

						
		if (!m_pMonster.empty())
		{
			for (iter; iter != iter_end; ++iter)
			{

				INFO Monster = (*iter)->GetInfo();

			
					if (CollsionCheck(m_pBuliding->GetInfo().x, m_pBuliding->GetInfo().y, m_pBuliding->GetInfo().size, m_pBuliding->GetInfo().size, Monster.x, Monster.y, Monster.size, Monster.size))
					{
						{
							m_pBuliding->BulidingLifeDown(((CMonster*)(*iter))->GetMonsterAttack());

							if (m_pBuliding->GetLife() <= 0)
							{
								delete m_pBuliding;
								//m_pBuliding = NULL;
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
