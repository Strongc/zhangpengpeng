// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#define WM_TETRIS_OVER		(WM_USER + 1)
#define WM_UPDATE_SCORES	(WM_USER + 2)

#define NODE_SIDE_LEN		20
#define GAP_WIDTH			20

#define H_DEVIATION			18
#define V_DEVIATION			57
