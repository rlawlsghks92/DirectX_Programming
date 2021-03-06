// DirectX_Programming.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DirectX_Programming.h"
#include "cMainGame.h"

#define MAX_LOADSTRING 100

HWND g_hWnd;
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pDevice = NULL;
D3DDISPLAYMODE g_Mode = { 1280,768, 0, D3DFMT_A8R8G8B8 };
cMainGame* g_pMain;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL InitWindows(_In_ HINSTANCE hInstance,	_In_opt_ HINSTANCE hPrevInstance,	_In_ LPWSTR    lpCmdLine,	_In_ int       nCmdShow);
BOOL InitProject();
void ReleaseProject();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	if ((InitWindows(hInstance, hPrevInstance, lpCmdLine, nCmdShow)) == FALSE)	return E_FAIL;
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECTXPROGRAMMING));
	if ((InitProject()) == FALSE) return E_FAIL;

    MSG msg;

	// 기본 메시지 루프입니다.
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (g_pMain)
			{
				g_pMain->Update();
				g_pMain->Draw();
			}
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTXPROGRAMMING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DIRECTXPROGRAMMING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0,0, g_Mode.Width, g_Mode.Height, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)	return FALSE;
	g_hWnd = hWnd;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_pMain)g_pMain->WndProc(hWnd, message, wParam, lParam);

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
		ReleaseProject();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

BOOL InitWindows(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DIRECTXPROGRAMMING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;

	return true;
}

BOOL InitProject()
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))	return E_FAIL;

	//Devie 객체의 성격을 결정하는데 이용
	D3DPRESENT_PARAMETERS param = {};
	param.Windowed = TRUE; //창화면이면 true, 전체화면이면 false
	param.SwapEffect = D3DSWAPEFFECT_DISCARD; //플리핑 체인의 버퍼가 교환되는 방법을 지정하는 D3DSWAPEFFECT 열거형 멤버, DISCARD를 지정하는 것이 가장 효과적이다 //더블버퍼와 같다
	param.AutoDepthStencilFormat = D3DFMT_D16; //깊이, 스텐실 버퍼의 포멧
	param.EnableAutoDepthStencil = TRUE; //뎁스 스텐실을 자동으로 사용하겟다
	
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &param, &g_pDevice);

	g_pMain = new cMainGame;
	g_pMain->Init();
	TIMEMANAGER->Init();


	return TRUE;
}

void ReleaseProject()
{
	SAFE_DELETE(g_pMain);
	SAFE_RELEASE(g_pDevice);
	SAFE_RELEASE(g_pD3D);
}
