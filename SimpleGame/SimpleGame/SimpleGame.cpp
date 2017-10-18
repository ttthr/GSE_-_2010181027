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

Renderer *g_Renderer = NULL;
CPlayer*      m_pPlayer = NULL;
CMonster*     m_pMonster = NULL ;
CSceneManager* m_pSceneManager = NULL;
list<CGameObject*> m_pGameObject;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	g_Renderer->DrawSolidRect(0, 0, 0, 20, 1, 0, 1, 1);

	g_Renderer->DrawSolidRect(m_pPlayer->GetInfo()->m_fx, m_pPlayer->GetInfo()->m_fy, 0, 40, 1, 0, 0, 1);
	m_pPlayer->Update();

	list<CGameObject*>::iterator iter = m_pGameObject.begin();
	list<CGameObject*>::iterator iter_end = m_pGameObject.end();

	for (iter; iter != iter_end; ++iter)
	{
		g_Renderer->DrawSolidRect((*iter)->GetInfo()->m_fx, (*iter)->GetInfo()->m_fy, 0, 20, 1, 1, 1, 1);
		(*iter)->Update();
	}
	/*g_Renderer->DrawSolidRect(m_pMonster->GetInfo()->m_fx, m_pMonster->GetInfo()->m_fy, 0, 40, 0.3, 0.3, 0.3, 0.3);
	m_pMonster->Update();*/
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
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

	
	m_pPlayer = new CPlayer();
	m_pPlayer->Initialize();
	
	for (int i = 0; i < 50; ++i)
	{
		CGameObject* pMonster = new CMonster;
		pMonster->Initialize();
		pMonster->SetPos(static_cast<float>(rand() % 300)
			, static_cast<float>(rand() % 300));

		m_pGameObject.push_back(pMonster);
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

	delete g_Renderer;

    return 0;
}

