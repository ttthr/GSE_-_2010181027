#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"


CGameObject::CGameObject()
{

	m_fspeed = 0.5;
	m_xDir = 1;
	m_yDir = 1;

}
CGameObject::~CGameObject()
{


}
void CGameObject::Initialize(void)
{
	
	m_Info.x = 30;
	m_Info.y = 30;
	m_Info.z = 0;
	m_Info.size = 30;


}

void CGameObject::Update(void)
{
	
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
