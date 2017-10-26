#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"


CGameObject::CGameObject()
{

	m_fspeed = 0.5;
	m_xDir = 1;
	m_yDir = 1;
	m_fLife = 210;
	m_fLifeTime = 1400.f;
	m_fAttack = 50.f;

}
CGameObject::~CGameObject()
{


}
void CGameObject::Initialize(void)
{
	
}

void CGameObject::Update(float _ElapsedTime)
{
	//타임 매니저 같은 역할을 하기 위한 변수 
	//float ElapsedTime = 0.1;


	m_Info.x += m_fspeed * m_xDir * _ElapsedTime;
	m_Info.y += m_fspeed * m_yDir * _ElapsedTime;

	if (m_Info.x > 250)
		m_xDir *= -1;
	else if (m_Info.x <= -250)
		m_xDir *= -1;


	if (m_Info.y > 250)
		m_yDir *= -1;
	else if (m_Info.y <= -250)
		m_yDir *= -1;

}

void CGameObject::SetInfo(INFO _Info)
{
	m_Info = _Info;
}

void CGameObject::SetColor(float r, float g, float b, float a)
{
	m_Info.r = r;
	m_Info.g = g;
	m_Info.b = b;
	m_Info.a = a;
}

void CGameObject::SetPos(float _fx, float _fy)
{
	m_Info.x = _fx;
	m_Info.y = _fy;
}

void CGameObject::SetDir(float _xDir, float _yDir)
{
	m_xDir = _xDir;
	m_yDir = _yDir;
}
