/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "SceneManager.h"

//Renderer*      g_Renderer = NULL;
CPlayer*       m_pPlayer = NULL;
CMonster*      m_pMonster = NULL ;
CSceneManager* m_pSceneManager = NULL;
bool b_LButtonDown = false;

void RenderScene(void)
{

	float CurrentTime, m_fStartTime, InitStartTime;

	InitStartTime = (float)timeGetTime() * 0.001f;
	m_fStartTime = InitStartTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 20, 1, 0, 1, 1);

	list<CGameObject*>* listGameObject = m_pSceneManager->GetgameObject();

	//플레이어 생성
	list<CGameObject*>::iterator iter_player = listGameObject->begin();
	list<CGameObject*>::iterator iter_playerend = listGameObject->end();

	for (iter_player; iter_player != iter_playerend; ++iter_player)
	{
		INFO Info = ((CPlayer*)(*iter_player))->GetInfo();

		m_pSceneManager->GetRenderer()->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);

	}

	//몬스터 생성
	list<CGameObject*>::iterator iter_monster = listGameObject->begin();
	list<CGameObject*>::iterator iter_monsterend = listGameObject->end();

	for (iter_monster; iter_monster != iter_monsterend; ++iter_monster)
	{
		INFO Info = ((CMonster*)(*iter_monster))->GetInfo();

		m_pSceneManager->GetRenderer()->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);

	}
	//씬 매니저 몬스터, 플레이어 업데이트
	m_pSceneManager->ObjectUpdate();

	// 씬 매니저에서 두 객체를 다 들고 있기 때문에 충돌함수 여기서 구현 후 업데이트에서 돌려주기
	m_pSceneManager->CollisionObject();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	// 클래시 로얄 처럼 카드를  누르고 드래그로 이동후 뗀 곳에 생성을 하기 위해
	switch (button)
	{
	case GLUT_LEFT_BUTTON:

		if (state == GLUT_DOWN)
		{
			b_LButtonDown = true;
		}
		if (state == GLUT_UP)
		{
			if (b_LButtonDown)
			{

				b_LButtonDown = false;
				m_pSceneManager->AddMonstergameObject(float(x - 250), float(-(y - 250)), 0, 20, 255, 255, 255, 0);
			}
		}
		break;


	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}


	// Initialize Renderer
	//g_Renderer = new Renderer(500, 500);


	// 플레이어 생성 및 Initialize
	m_pPlayer = new CPlayer();
	m_pPlayer->Initialize();

	// 몬스터 생성 및 Initialize
	m_pMonster = new CMonster();
	m_pMonster->Initialize();

	// 씬매니저로 객체 생성 관리 list사용
	m_pSceneManager = new CSceneManager();
	
	// 씬 매니저 이용 PlayerObject 생성
	m_pSceneManager->AddgamePlayerObject(m_pPlayer->GetInfo().x , m_pPlayer->GetInfo().y, m_pPlayer->GetInfo().z, m_pPlayer->GetInfo().size, 0, 0, 255, 255);

	for (int i = 0; i < 50; ++i)
	{
		// 씬 매니저 이용 MonstergameObject 50개 생성 ( for문 이용 )
		m_pSceneManager->AddMonstergameObject(float(rand() % 500 - 250), float(rand() % 500 - 250), m_pMonster->GetInfo().z, m_pMonster->GetInfo().size, 255, 255, 255, 0);
	}




	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	//객체 삭제
	delete m_pSceneManager;
	delete m_pPlayer;
	delete m_pMonster;

    return 0;
}

