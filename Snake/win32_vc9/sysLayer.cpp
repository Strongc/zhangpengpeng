#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
extern "C" {
#include "../src/sysLayer.h"
}

extern HWND g_hMainWnd;
extern HDC g_hDC;

DWORD gs_dwLoopTime = 1000;
HANDLE gs_hEventExit = NULL;
HANDLE gs_hSysThread = NULL;
BOOL gs_bPause = FALSE;

HBRUSH gs_hBrush_Food;
HBRUSH gs_hBrush_Snake;
HBRUSH gs_hBrush_Empty;

const int iNodeWidth = MAINWIN_WIDTH / WORLD_WIDTH;
const int iNodeHeight = MAINWIN_HEIGHT / WORLD_HEIGHT;

extern "C" int draw_one_node(int x, int y, int type)
{
	RECT rc;
	rc.left  = x * iNodeWidth;
	rc.top = y * iNodeHeight;
	rc.right = rc.left + iNodeWidth;
	rc.bottom = rc.top + iNodeHeight;

	if (type == TILE_TYPE_FOOD)
		FillRect(g_hDC, &rc, gs_hBrush_Food);
	else if (type == TILE_TYPE_SNAKE)
		FillRect(g_hDC, &rc, gs_hBrush_Snake);
	else
		FillRect(g_hDC, &rc, gs_hBrush_Empty);

	return 1;
}

extern "C" int random(int range)
{
	time_t now;
	srand((unsigned int)time(&now));
	return rand() % range;
}

int Sys_Init()
{
	gs_hEventExit = CreateEvent(NULL, FALSE, FALSE, NULL);
	gs_hBrush_Food = CreateSolidBrush(RGB(255, 0, 0));
	gs_hBrush_Snake = CreateSolidBrush(RGB(0, 255, 0));
	gs_hBrush_Empty = CreateSolidBrush(RGB(255, 255, 255));
	snake_init_all();
	return 0;
}

int Sys_Uninit()
{
	CloseHandle(gs_hEventExit);
	return 0;
}

DWORD WINAPI _Sys_Snake_Loop(LPVOID lpParam)
{
	int iRet = 0;
	while (WaitForSingleObject(gs_hEventExit, gs_dwLoopTime) == WAIT_TIMEOUT)
	{
		if (gs_bPause)
			continue;

		iRet = snake_one_step();
		switch (iRet)
		{
		case SNAKE_STATE_DIED:
			PostMessage(g_hMainWnd, WM_SNAKE_DIED, 0, 0);
			SetEvent(gs_hEventExit);
			break;
		case SNAKE_STATE_EATEN_FOOD:
			if (gs_dwLoopTime > 200)
				gs_dwLoopTime -= 20;
			break;
		case SNAKE_STATE_SUCCESS:
			PostMessage(g_hMainWnd, WM_SNAKE_SUCCESS, 0, 0);
			SetEvent(gs_hEventExit);
		default:
			break;
		}
	}
	return 0;
}

int Sys_Start()
{
	ResetEvent(gs_hEventExit);
	gs_hSysThread = CreateThread(NULL, 0, _Sys_Snake_Loop, NULL, 0, NULL);
	return 0;
}

int Sys_Stop()
{
	if (gs_hSysThread)
	{
		SetEvent(gs_hEventExit);
		WaitForSingleObject(gs_hSysThread, INFINITE);
		gs_hSysThread = NULL;
	}
	return 0;
}

int Sys_PressKey(int iDrc)
{
	int iSnakeDrc = SNAKE_DRC_UP;
	switch (iDrc)
	{
	case VK_UP:
		iSnakeDrc = SNAKE_DRC_UP;
		break;
	case VK_DOWN:
		iSnakeDrc = SNAKE_DRC_DOWN;
		break;
	case VK_RIGHT:
		iSnakeDrc = SNAKE_DRC_RIGHT;
		break;
	case VK_LEFT:
		iSnakeDrc = SNAKE_DRC_LEFT;
		break;
	case VK_SPACE:
		gs_bPause = !gs_bPause;
		break;
	default:
		break;
	}
	return snake_set_direction(iSnakeDrc);
}
