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

Renderer*      g_Renderer = NULL;
CPlayer*       m_pPlayer = NULL;
CMonster*      m_pMonster = NULL ;
CSceneManager* m_pSceneManager = NULL;
bool b_LButtonDown = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 20, 1, 0, 1, 1);


	list<CGameObject*>* listGameObject = m_pSceneManager->GetgameObject();

	//�÷��̾� ����
	list<CGameObject*>::iterator iter_player    = listGameObject->begin();
	list<CGameObject*>::iterator iter_playerend = listGameObject->end();

	for (iter_player; iter_player != iter_playerend; ++iter_player)
	{
		INFO Info = ((CPlayer*)(*iter_player))->GetInfo();

		g_Renderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);

		//�÷��̾� ������Ʈ ���� ĳ����
		((CPlayer*)(*iter_player))->Update();
		
	}

	//���� ����
	list<CGameObject*>::iterator iter_monster    = listGameObject->begin();
	list<CGameObject*>::iterator iter_monsterend = listGameObject->end(); 
	
		for (iter_monster; iter_monster != iter_monsterend; ++iter_monster)
		{
			INFO Info = ((CMonster*)(*iter_monster))->GetInfo();

			g_Renderer->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);


			//���� ������Ʈ ���� ĳ����
			((CMonster*)(*iter_monster))->Update();
	
		}

		// �� �Ŵ������� �� ��ü�� �� ��� �ֱ� ������ �浹�Լ� ���⼭ ���� �� ������Ʈ���� �����ֱ�
		m_pSceneManager->CollisionObject();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	// Ŭ���� �ξ� ó�� ī�带  ������ �巡�׷� �̵��� �� ���� ������ �ϱ� ����
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
	g_Renderer = new Renderer(500, 500);


	// �÷��̾� ���� �� Initialize
	m_pPlayer = new CPlayer();
	m_pPlayer->Initialize();

	// ���� ���� �� Initialize
	m_pMonster = new CMonster();
	m_pMonster->Initialize();

	// ���Ŵ����� ��ü ���� ���� list���
	m_pSceneManager = new CSceneManager();
	
	// �� �Ŵ��� �̿� PlayerObject ����
	m_pSceneManager->AddgamePlayerObject(m_pPlayer->GetInfo().x , m_pPlayer->GetInfo().y, m_pPlayer->GetInfo().z, m_pPlayer->GetInfo().size, 0, 0, 255, 255);

	for (int i = 0; i < 50; ++i)
	{
		// �� �Ŵ��� �̿� MonstergameObject 50�� ���� ( for�� �̿� )
		m_pSceneManager->AddMonstergameObject(float(rand() % 500 - 250), float(rand() % 500 - 250), m_pMonster->GetInfo().z, m_pMonster->GetInfo().size, 255, 255, 255, 0);
	}

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	//��ü ����
	delete g_Renderer;
	delete m_pSceneManager;
	delete m_pPlayer;
	delete m_pMonster;

    return 0;
}

