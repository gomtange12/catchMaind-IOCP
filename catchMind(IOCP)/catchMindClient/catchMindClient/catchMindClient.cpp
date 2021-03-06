#include "stdafx.h"
#include "GameFrameWork.h"
#include "Network.h"
#include "ChatManager.h"
#include "Login.h"
#include "InputManager.h"
#include "BrushManager.h"
#include "SceneManager.h"
#include "PlayerManager.h"
HINSTANCE hInst;
LPCTSTR lpszClass = TEXT("CatchMind _ CheonK1");
HWND hWnd;

LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);
ATOM myRegisterClass(HINSTANCE hInstance);
BOOL initInstance(HINSTANCE hInstance, int nCmdShow);
void releaseClient();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(254);

	myRegisterClass(hInstance);
	if (!initInstance(hInstance, nCmdShow))
		return FALSE;

	Network::getInstance()->initNetwork(hWnd);
	GameFrameWork::getInstance()->init(hWnd);
	Login::getInstance()->initLogin(hWnd, hInst);

	MSG msg;
	while (true)
	{
		/// 메시지큐에 메시지가 있으면 메시지 처리
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GameFrameWork::getInstance()->update();
		}
	}

	releaseClient();
	Network::getInstance()->releaseNetwork();
	Network::getInstance()->releaseInstance();
	return (int)msg.wParam;
}
ATOM myRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WndClass.lpfnWndProc = wndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;

	return RegisterClass(&WndClass);
}

BOOL initInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT,
		SCREENWIDTH, SCREENHIGHT, NULL, (HMENU)NULL, hInstance, NULL);

	if (!hWnd)
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
LRESULT CALLBACK wndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	char id[50];
	char pw[50];
	static int sx, sy, oldx, oldy;
	static bool nowDraw =false;
	switch (iMessage)
	{
	case WM_SOCKET:
		Network::getInstance()->processSocketMessage(hWnd, iMessage, wParam, lParam);
		InvalidateRect(hWnd, NULL, false);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_LOGIN:
		{
			Login::getInstance()->getWinText(id, pw, 50);
			Login::getInstance()->loginInfo(id, pw);
			break;
		}
		}
		return 0;
	case WM_CHAR:
		ChatManager::getInstance()->pushWord(wParam);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			ChatManager::getInstance()->pushEndterKey();
			break;
		case VK_BACK:
			ChatManager::getInstance()->pushRemoveKey();
			break;
		}
		break;

	case WM_MOUSEMOVE:
	{
		if (SceneManager::getInstance()->getSceneNum() == SCENE_GAME && BrushManager::getInstance()->checkMyTurn()==true) {
			if (InputManager::getInstance()->checkLButton()) {
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(hWnd, &pt);
				if (745 >= pt.x && pt.x >= 250 && 507 >= pt.y && pt.y >= 195) {
					BrushManager::getInstance()->oldPt = pt;
					BrushManager::getInstance()->drawBrush();
				}
				
			}
		}

	}
	break;
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
void releaseClient()
{
	Login::getInstance()->releaseInstance();
	
	GameFrameWork::getInstance()->release();
	GameFrameWork::getInstance()->releaseInstance();
}