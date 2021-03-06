// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;

#define SAFE_DELETE(p) if(p) { delete(p); (p) = nullptr;}
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = nullptr;}

#define GETSET(varType, varName, funcName) protected:\
varType varName;\
public:\
	varType Get##funcName()\
	{\
		return varName;\
	}\
	void Set##funcName(varType var)\
	{\
		varName = var;\
	}

#define GET(varType, varName, funcName) protected:\
	varType			varName;\
public:\
	varType Get##funcName()\
	{\
		return varName;\
	}

#define SET(varType, varName, funcName) protected:\
	varType			varName;\
public:\
	void Set##funcName(varType var)\
	{\
		varName = var;\
	}

#include "cTimeManager.h"
#include "InputManager.h"
#include "cButton.h"
#include <time.h>

#define KEYBOARD InputManager::GetInstance()
#define TIMEMANAGER cTimeManager::GetInstance()
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
extern LPDIRECT3DDEVICE9 g_pDevice;
extern D3DDISPLAYMODE g_Mode;
extern HWND g_hWnd;
