#include "stdafx.h"
#include "SceneManager.h"


CSceneManager::CSceneManager()
{
	
}


CSceneManager::~CSceneManager()
{

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

	// ·£´ýÇÑ¹æÇâ 
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
void CSceneManager::UpdateMonsterObject()
{
	list<CGameObject*>::iterator iter     = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject.end();

	for (iter; iter != iter_end; ++iter)
	{
		((CMonster*)(*iter))->Update();
	}
}
void CSceneManager::UpdatePlayerObject()
{
	list<CGameObject*>::iterator iter = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject.end();

	for (iter; iter != iter_end; ++iter)
	{
		((CPlayer*)(*iter))->Update();
	}
}
void CSceneManager::ReleaseObject()
{
	list<CGameObject*>::iterator iter = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject.end();

	for (iter; iter != iter_end; ++iter)
	{
		delete (*iter);

		iter = m_pGameObject.erase(iter);
	}

}
