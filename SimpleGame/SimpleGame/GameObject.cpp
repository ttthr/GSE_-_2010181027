#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"


CGameObject::CGameObject()
{
	

}
CGameObject::~CGameObject()
{


}
void CGameObject::Initialize(void)
{
	m_Info.m_fx = 5;
	m_Info.m_fy = 5;
	m_Info.m_FCX = 40;
	m_Info.m_FCY = 40;

}

void CGameObject::Update(void)
{

}

void CGameObject::SetPos(float _fx, float _fy)
{
	m_Info.m_fx = _fx;
	m_Info.m_fy = _fy;
}
