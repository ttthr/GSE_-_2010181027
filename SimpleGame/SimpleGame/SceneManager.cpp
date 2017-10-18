#include "stdafx.h"
#include "SceneManager.h"


CSceneManager::CSceneManager()
{
	
}


CSceneManager::~CSceneManager()
{

}

void CSceneManager::Initialize(void)
{
	list<CGameObject*>::iterator iter = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject.end();

	for (iter; iter != iter_end; ++iter)
	{
		(*iter)->Initialize();
	}
}

void CSceneManager::Update(void)
{
	list<CGameObject*>::iterator iter = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject.end();

	for (iter; iter != iter_end; ++iter)
	{
		(*iter)->Update();
	}
}

void CSceneManager::SetPos(float _fx, float _fy)
{
	list<CGameObject*>::iterator iter = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject.end();

	for (iter; iter != iter_end; ++iter)
	{
		(*iter)->SetPos(200, 200);
	}
}

