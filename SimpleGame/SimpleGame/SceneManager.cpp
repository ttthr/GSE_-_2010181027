#include "stdafx.h"
#include "SceneManager.h"
#include "Bullet.h"

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
		static_cast<CBuliding*>(pGameObject)->SetBullet(&m_pGameObject[OBJECT_ARROW]);
		break;
	case OBJECT_CHARACTER:
		pGameObject = new CMonster();
		static_cast<CMonster*>(pGameObject)->SetBullet(&m_pGameObject[OBJECT_BULLET]);
		break;
	default:
		return;
	}

	//���� ����
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

		// ���� ������Ʈ
		list<CGameObject*>::iterator iter = m_pGameObject[i].begin();

		for (iter; iter != m_pGameObject[i].end();)
		{
			//�Ѿ˰� ������ ������Ÿ���� 2000.f �̰� 
			// �� ������ 1�� �ް��ؼ� �ð��� �ٵǸ� return 1Ÿ�� ����
			(*iter)->DecreaseLifeTime(1.f);
			//���� ��ü�� ������Ʈ ����� ��´�.
			int iResult = (*iter)->Update(_ElapsedTime);
				
			//���� ������ ����ó��
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
	//���� ����
	for (int i = 0; i <= OBJECT_BUILDING; ++i)
	{
		list<CGameObject*>::iterator iter = m_pGameObject[OBJECT_BUILDING].begin();
		list<CGameObject*>::iterator iter_end = m_pGameObject[OBJECT_BUILDING].end();

		{
			for (iter; iter != iter_end; ++iter)
			{
				INFO Info = (*iter)->GetInfo();
				m_TextureBuilding = m_pRenderer->CreatePngTexture("../../Resource/BuildingTexture.png");
				m_pRenderer->DrawTexturedRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a, m_TextureBuilding);
			
			}
		}
	}
	//ĳ���� ����
	for (int i = 0; i < OBJECT_CHARACTER; ++i)
	{
		
		list<CGameObject*>::iterator iter     = m_pGameObject[OBJECT_CHARACTER].begin();
		list<CGameObject*>::iterator iter_end = m_pGameObject[OBJECT_CHARACTER].end();

		for (iter; iter != iter_end; ++iter)
		{
			INFO Info = (*iter)->GetInfo();
			m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);

		}
	}
	//ĳ���� �ҷ� ����
	for (int i = 0; i < OBJECT_BULLET; ++i)
	{

		list<CGameObject*>::iterator iter = m_pGameObject[OBJECT_BULLET].begin();
		list<CGameObject*>::iterator iter_end = m_pGameObject[OBJECT_BULLET].end();

		for (iter; iter != iter_end; ++iter)
		{
			INFO Info = (*iter)->GetInfo();
			m_pRenderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);

		}
	}
	//���� �ҷ� ����
	for (int i = 0; i < OBJECT_ARROW; ++i)
	{

		list<CGameObject*>::iterator iter = m_pGameObject[OBJECT_ARROW].begin();
		list<CGameObject*>::iterator iter_end = m_pGameObject[OBJECT_ARROW].end();

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
				//�Ұ����� ���� �浹�Ǿ��ٰ� �Ǵ� ��Ŵ
				bCollCheck = true;
				break;
			}

		}

		if (bCollCheck == true)
		{
			//�浹�Ǿ����� ����
			(*iter)->SetColor(255, 0, 0, 255);
		}
		else
		{
			//�ƴ϶�� ���
			(*iter)->SetColor(255, 255, 255, 0);
		}

	}

}


void CSceneManager::BulletMonsetrColl(OBJECT_TYPE _type)
{
	if (m_pGameObject[OBJECT_ARROW].empty() || m_pGameObject[_type].empty())
		return;

	list<CGameObject*>::iterator iterMonster     = m_pGameObject[_type].begin();
	list<CGameObject*>::iterator iterMonster_end = m_pGameObject[_type].end();

	for (iterMonster; iterMonster != iterMonster_end; ++iterMonster)
	{
	   
		list<CGameObject*>::iterator iter = m_pGameObject[OBJECT_ARROW].begin();

		for (iter; iter != m_pGameObject[OBJECT_ARROW].end(); ++iter)
 		{
			INFO Bullet = (*iter)->GetInfo();
			INFO Monster = (*iterMonster)->GetInfo();

			if (CollsionCheck(Bullet.x, Bullet.y, Bullet.size, Bullet.size, Monster.x, Monster.y, Monster.size, Monster.size))
			{
				
					(*iterMonster)->DecreaseLife((*iter)->GetAttack());

					(*iter)->SetDeadCheck();

					if ((*iterMonster)->GetLife() <= 0)
					{
						(*iterMonster)->SetDeadCheck();
					}
			
			
			}

		}
	}

}

void CSceneManager::BulletBulidingColl(OBJECT_TYPE _type)
{
	if (m_pGameObject[OBJECT_BULLET].empty() || m_pGameObject[_type].empty())
		return;

	list<CGameObject*>::iterator iterMonster = m_pGameObject[_type].begin();
	list<CGameObject*>::iterator iterMonster_end = m_pGameObject[_type].end();

	for (iterMonster; iterMonster != iterMonster_end; ++iterMonster)
	{

		list<CGameObject*>::iterator iter = m_pGameObject[OBJECT_BULLET].begin();

		for (iter; iter != m_pGameObject[OBJECT_BULLET].end(); ++iter)
		{
			INFO Bullet = (*iter)->GetInfo();
			INFO Monster = (*iterMonster)->GetInfo();

			if (CollsionCheck(Bullet.x, Bullet.y, Bullet.size, Bullet.size, Monster.x, Monster.y, Monster.size, Monster.size))
			{

				(*iterMonster)->DecreaseLife((*iter)->GetAttack());

				(*iter)->SetDeadCheck();

				if ((*iterMonster)->GetLife() <= 0)
				{
					(*iterMonster)->SetDeadCheck();
				}


			}

		}
	}
}


void CSceneManager::BulidingMonsterColl()
{

	if (m_pGameObject[OBJECT_CHARACTER].empty())
		return;

	list<CGameObject*>::iterator iterMonster      = m_pGameObject[OBJECT_CHARACTER].begin();
	list<CGameObject*>::iterator iterMonster_end = m_pGameObject[OBJECT_CHARACTER].end();

	for (iterMonster; iterMonster != iterMonster_end; ++iterMonster)
	{
		list<CGameObject*>::iterator iter = m_pGameObject[OBJECT_BUILDING].begin();

		for (iter; iter != m_pGameObject[OBJECT_BUILDING].end();++iter)
		{
			INFO Buliding = (*iter)->GetInfo();
			INFO Monster = (*iterMonster)->GetInfo();

			if (!m_pGameObject[OBJECT_BUILDING].empty())
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
	// API ��Ʈ  �浹 �Լ� ���θ� ����ϰ� ����
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
