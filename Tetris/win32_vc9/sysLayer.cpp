#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern "C" {
#include "../src/sysLayer.h"
}

extern HWND g_hMainWnd;
extern HDC g_hDC;

#define ORIGIN_LOOP_TIME  1000

DWORD gs_dwLoopTime = ORIGIN_LOOP_TIME;
HANDLE gs_hEventExit = NULL;
HANDLE gs_hSysThread = NULL;
BOOL gs_bPause = FALSE;

HBRUSH gs_hBrush_Colors[5];

extern "C" int draw_one_block(int x, int y, int type)
{
	RECT rc;
	rc.left  = y * NODE_SIDE_LEN;
	rc.top = x * NODE_SIDE_LEN;
	rc.right = rc.left + NODE_SIDE_LEN;
	rc.bottom = rc.top + NODE_SIDE_LEN;

	FillRect(g_hDC, &rc, gs_hBrush_Colors[type]);

	return 1;
}

extern "C" int random(int range)
{
	time_t now;
	srand((unsigned int)time(&now));
	return rand() % range;
}

void draw_scores(int scores)
{
	RECT rc;
	rc.left = NODE_SIDE_LEN * WORLD_WIDTH + GAP_WIDTH / 2;
	rc.right = rc.left + NODE_SIDE_LEN * 4;
	rc.top = NODE_SIDE_LEN * 2;
	rc.bottom = rc.top + NODE_SIDE_LEN;
	char scores_txt[32];
	itoa(scores, scores_txt, 10);
	DrawText(g_hDC, scores_txt, -1, &rc, DT_VCENTER|DT_CENTER);
}

void draw_nextsharp(int color, const int form[SIDE_LEN][SIDE_LEN])
{
	int i, j;
	for (i = 0; i < SIDE_LEN; i++)
	{
		for (j = 0; j < SIDE_LEN; j++)
		{
			RECT sharp_rc;
			sharp_rc.left  = NODE_SIDE_LEN * WORLD_WIDTH + GAP_WIDTH / 2 + j * NODE_SIDE_LEN;
			sharp_rc.top = (3 + i) * NODE_SIDE_LEN;
			sharp_rc.right = sharp_rc.left + NODE_SIDE_LEN;
			sharp_rc.bottom = sharp_rc.top + NODE_SIDE_LEN;

			if (form[i][j])
				FillRect(g_hDC, &sharp_rc, gs_hBrush_Colors[color]);
			else
				FillRect(g_hDC, &sharp_rc, gs_hBrush_Colors[COLOR_BLANK]);
		}
	}
}

int Sys_Init()
{
	gs_hEventExit = CreateEvent(NULL, FALSE, FALSE, NULL);
	gs_hBrush_Colors[0] = CreateSolidBrush(RGB(255, 255, 255));
	gs_hBrush_Colors[1] = CreateSolidBrush(RGB(255, 0, 0));
	gs_hBrush_Colors[2] = CreateSolidBrush(RGB(155, 155, 0));
	gs_hBrush_Colors[3] = CreateSolidBrush(RGB(0, 155, 0));
	gs_hBrush_Colors[4] = CreateSolidBrush(RGB(0, 0, 255));
	tetris_init_all();

	MoveToEx(g_hDC, NODE_SIDE_LEN * WORLD_WIDTH, 0, NULL);
	LineTo(g_hDC, NODE_SIDE_LEN * WORLD_WIDTH, NODE_SIDE_LEN * WORLD_HEIGHT + V_DEVIATION);

	RECT rc;
	rc.left = NODE_SIDE_LEN * WORLD_WIDTH + GAP_WIDTH / 2;
	rc.right = rc.left + NODE_SIDE_LEN * 4;
	rc.top = NODE_SIDE_LEN;
	rc.bottom = rc.top + NODE_SIDE_LEN;
	DrawText(g_hDC, "Scores", -1, &rc, DT_VCENTER|DT_CENTER);
	rc.top = rc.bottom + NODE_SIDE_LEN;
	rc.bottom = rc.top + NODE_SIDE_LEN;
	DrawText(g_hDC, "Next Sharp", -1, &rc, DT_VCENTER|DT_CENTER);

	int color;
	const int (*form)[SIDE_LEN][SIDE_LEN];
	tetris_get_next_sharp(&color, &form);
	draw_nextsharp(color, *form);
	draw_scores(tetris_get_scores());

	return 0;
}

int Sys_Uninit()
{
	CloseHandle(gs_hEventExit);
	return 0;
}

DWORD WINAPI _Sys_Tetris_Loop(LPVOID lpParam)
{
	int iRet = 0;
	int color;
	const int (*form)[SIDE_LEN][SIDE_LEN];
	while (WaitForSingleObject(gs_hEventExit, gs_dwLoopTime) == WAIT_TIMEOUT)
	{
		if (gs_bPause)
			continue;

		iRet = tetris_one_step();
		if (iRet & TETRIS_STATE_OVER)
		{
			PostMessage(g_hMainWnd, WM_TETRIS_OVER, 0, 0);
			SetEvent(gs_hEventExit);
			break;
		}
		if(iRet & TETRIS_STATE_DROPPEN)
		{
			if (gs_dwLoopTime != ORIGIN_LOOP_TIME)
				gs_dwLoopTime = ORIGIN_LOOP_TIME;
			tetris_get_next_sharp(&color, &form);
			draw_nextsharp(color, *form);
		}
		if (iRet & TETRIS_STATE_VANISH)
		{
			PostMessage(g_hMainWnd, WM_UPDATE_SCORES, (WPARAM)tetris_get_scores(), 0);
		}
	}
	return 0;
}

int Sys_Start()
{
	ResetEvent(gs_hEventExit);
	gs_hSysThread = CreateThread(NULL, 0, _Sys_Tetris_Loop, NULL, 0, NULL);
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
	switch (iDrc)
	{
	case VK_UP:
		tetris_rotate();
		break;
	case VK_DOWN:
		gs_dwLoopTime = ORIGIN_LOOP_TIME / 10;
		break;
	case VK_RIGHT:
		tetris_h_move(1);
		break;
	case VK_LEFT:
		tetris_h_move(0);
		break;
	case VK_SPACE:
		gs_bPause = !gs_bPause;
		break;
	default:
		break;
	}
	return 0;
}

void Sys_UpdateScores(int scores)
{
	draw_scores(scores);
}