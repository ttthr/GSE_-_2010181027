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
float m_fTeam1CreateTime = 1.f;
float m_fTeam2CreateTime = 2.f;

void RenderScene(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	//���� �ð����� ����ϱ�
	float ElapsedTime = float(timeGetTime() - d_StratTime) / 1000.f;
	d_StratTime = timeGetTime();

	//CreateTime
	m_fTeam1CreateTime -= ElapsedTime;
	m_fTeam2CreateTime -= ElapsedTime;


	//�� �Ŵ����� ������Ʈ ������Ʈ
	m_pSceneManager->ObjectUpdate(ElapsedTime);

	//�� �Ŵ����� ����

	m_pSceneManager->Render();

	//�� ����
	m_pSceneManager->GetRenderer()->DrawSolidRect(0, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(30, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(60, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(90, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(120, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(150, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(180, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(210, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(240, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(0, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(-30, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(-60, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(-90, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(-120, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(-150, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(-180, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(-210, 0, 0, 10, 255, 255, 255, 255);
	m_pSceneManager->GetRenderer()->DrawSolidRect(-240, 0, 0, 10, 255, 255, 255, 255);

	// �� �Ŵ������� ������Ʈ���� �浹��Ų��
    //���� �ҷ��� ���� �浹
	m_pSceneManager->BulletColl(OBJECT_ARROW_TEAM2 , OBJECT_CHARACTER_TEAM1);
	m_pSceneManager->BulletColl(OBJECT_ARROW_TEAM1 , OBJECT_CHARACTER_TEAM2);

	//���� �ҷ��� ���� �浹
	m_pSceneManager->BulletColl(OBJECT_BULLET_TEAM2, OBJECT_TEAM1);
	m_pSceneManager->BulletColl(OBJECT_BULLET_TEAM1, OBJECT_TEAM2);

	//TEAM1 ���Ϳ� TEAM2 ���� �Ѿ��浹
	m_pSceneManager->BulletColl(OBJECT_BULLET_TEAM2, OBJECT_CHARACTER_TEAM1);
	m_pSceneManager->BulletColl(OBJECT_BULLET_TEAM1, OBJECT_CHARACTER_TEAM2);

	//������ ���� �浹
	m_pSceneManager->BulidingMonsterColl(OBJECT_TEAM2, OBJECT_CHARACTER_TEAM1);
	m_pSceneManager->BulidingMonsterColl(OBJECT_TEAM1, OBJECT_CHARACTER_TEAM2);

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

				if (400 - y < 0)	// ���������̸� Ż�� 
				{
					if (m_fTeam2CreateTime < 0)
					{
						m_pSceneManager->AddActorObject(float(x - 250), float(-(y - 400)), OBJECT_CHARACTER_TEAM2);
						m_fTeam2CreateTime = 2.f; //2�ʸ��� �����ϰ�
					
					}
					break;
				}

				else if (400 - y > 0)	// ���������̸� Ż�� 
				{
					if (m_fTeam1CreateTime < 0)
					{
						m_pSceneManager->AddActorObject(float(x - 250), float(-(y - 400)), OBJECT_CHARACTER_TEAM1);
						m_fTeam1CreateTime = 1.f; //1�ʸ��� �����ϰ�
						
					}
					break;
					
				}
			}
		}
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
	glutInitWindowSize(500, 800);
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

	// ���� ��
	srand((unsigned)time(NULL));

	// ó�� �ð�
	d_StratTime = timeGetTime();

	// ���Ŵ����� ��ü ���� ���� list���
	m_pSceneManager = new CSceneManager();

	//TEAM1 ���� ���� ���� 3�� ��������
	m_pSceneManager->AddActorObject(0, 300, OBJECT_TEAM1);
	m_pSceneManager->AddActorObject(150, 250, OBJECT_TEAM1);
	m_pSceneManager->AddActorObject(-150, 250, OBJECT_TEAM1);
	
	//TEMA2 �Ʒ� ���� ����3�� ��������
	m_pSceneManager->AddActorObject(0, -300, OBJECT_TEAM2);
	m_pSceneManager->AddActorObject(150, -250, OBJECT_TEAM2);
	m_pSceneManager->AddActorObject(-150, -250, OBJECT_TEAM2);


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

