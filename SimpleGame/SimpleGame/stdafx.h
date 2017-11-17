#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <time.h>

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

typedef enum
{
	OBJECT_TEAM1,
	OBJECT_TEAM2,
	OBJECT_CHARACTER_TEAM1,
	OBJECT_CHARACTER_TEAM2,
	OBJECT_BULLET_TEAM1,
	OBJECT_BULLET_TEAM2,
	OBJECT_ARROW_TEAM1,
	OBJECT_ARROW_TEAM2,
	OBJECT_END

}OBJECT_TYPE;
