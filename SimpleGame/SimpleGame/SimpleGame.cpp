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

	//실제 시간으로 계산하기
	float ElapsedTime = (timeGetTime() - d_StratTime) / 5.f;
	d_StratTime = timeGetTime();


	//씬 매니저로 오브젝트 업데이트
	m_pSceneManager->ObjectUpdate(ElapsedTime);

	//씬 매니저로 랜더

	m_pSceneManager->Render();
	// 씬 매니저에서 오브젝트들을 충돌시킨다.
	//m_pSceneManager->CollisionObject();
	m_pSceneManager->MonsterBulletColl();
	//m_pSceneManager->BulidingMonsterColl();

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
				m_pSceneManager->AddMonsterObject(float(x - 250), float(-(y - 250)), OBJECT_CHARACTER);
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

	// 처음 시간
	d_StratTime = timeGetTime();

	// 씬매니저로 객체 생성 관리 list사용
	m_pSceneManager = new CSceneManager();

		// 씬 매니저 이용 gameObject 50개 생성 ( for문 이용 )
	for (int i = 0; i < 30; ++i)
	{
		m_pSceneManager->AddMonsterObject(float(rand() % 500 - 250), float(rand() % 500 - 250), OBJECT_CHARACTER);
	}

	m_pSceneManager->AddBuliding(OBJECT_BUILDING);


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	//객체 삭제
	delete m_pSceneManager;

    return 0;
}

