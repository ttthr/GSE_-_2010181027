#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>

using namespace std;

#include <Windows.h>
#include <list>
#include <algorithm>

//struct INFO
//{
//	float m_fx;
//	float m_fy;
//	float m_FCX;
//	float m_FCY;
//};

typedef struct INFO
{
	float x;
	float y;
	float z;
	float size;
	float r;
	float g;
	float b;
	float a;
}INFO;

enum eDirType
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_UP_L,
	DIR_UP_R,
	DIR_DOWN,
	DIR_END,
};