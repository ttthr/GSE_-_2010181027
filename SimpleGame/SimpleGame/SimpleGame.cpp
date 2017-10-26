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
#include "SceneManager.h"

CSceneManager* m_pSceneManager = NULL;
bool b_LButtonDown = false;
DWORD d_StratTime = 0;

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	//���� �ð����� ����ϱ�
	float ElapsedTime = (timeGetTime() - d_StratTime) / 5.f;
	d_StratTime = timeGetTime();


	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 20, 1, 0, 1, 1);

	list<CGameObject*>* listGameObject = m_pSceneManager->GetgameObject();

	//������Ʈ ����
	list<CGameObject*>::iterator iter = listGameObject->begin();
	list<CGameObject*>::iterator iter_end= listGameObject->end();

	for (iter; iter != iter_end; ++iter)
	{
		INFO Info = (*iter)->GetInfo();

		m_pSceneManager->GetRenderer()->DrawSolidRect(Info.x, Info.y, Info.z, Info.size, Info.r, Info.g, Info.b, Info.a);

	}
	//�� �Ŵ����� ������Ʈ ������Ʈ
	m_pSceneManager->ObjectUpdate(ElapsedTime);

	// �� �Ŵ������� ������Ʈ���� �浹��Ų��.
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
				m_pSceneManager->AddgameObject(float(x - 250), float(-(y - 250)), 0, 20, 255, 255, 255, 0);
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

	// ó�� �ð�
	d_StratTime = timeGetTime();

	// ���Ŵ����� ��ü ���� ���� list���
	m_pSceneManager = new CSceneManager();

	for (int i = 0; i < 50; ++i)
	{
		// �� �Ŵ��� �̿� gameObject 50�� ���� ( for�� �̿� )
		m_pSceneManager->AddgameObject(float(rand() % 500 - 250), float(rand() % 500 - 250), 0, 20, 255, 255, 255, 0);
	}
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	//��ü ����
	delete m_pSceneManager;

    return 0;
}

