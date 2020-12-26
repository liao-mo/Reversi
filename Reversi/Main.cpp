//Name: 廖墨哲
//ID: B10815026
//Date: 2020/12/26
//Title: Reversi game

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <iostream>
#include <mmsystem.h>
#include "Reversi.h"
#pragma comment(lib, "winmm.lib")

using namespace std;

Reversi reversi;

LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

void KeyDownEvent( WPARAM wParam )
{
	//==== Tab、Enter、Ctrl... ====//
	if( wParam == VK_TAB )
	{
		//cout << "Tab Down" << endl;
	}

	//==== 英文字母或數字 ====//
	//set button status
	for (int i = 0; i < 8; i++)
	{
		if (wParam == 'a' + i || wParam == 'A' + i)
			reversi.buttonAtoH[i] = true;
		if (wParam == '1' + i)
			reversi.button1to8[i] = true;
	}

	reversi.buttonPressed();
	reversi.updataScreen();
}

void KeyUpEvent( WPARAM wParam )
{
	//==== Tab、Enter、Ctrl... ====//
	if( wParam == VK_TAB )
	{
		//cout << "Tab Up" << endl;
	}

	//==== 英文字母或數字 ====//
	//clean all button status
	for (int i = 0; i < 8; i++)
	{
		if (wParam == 'a' + i || wParam == 'A' + i)
		reversi.buttonAtoH[i] = false;
		if (wParam == '1' + i)
		reversi.button1to8[i] = false;
	}

	reversi.updataScreen();
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow )
{
	//==== 註冊視窗類別 ====//
	const wchar_t CLASS_NAME[]  = L"Sample Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass( &wc );

	//==== 創建視窗 ====//
	HWND hwnd = CreateWindowEx(
		0,                      // Optional window styles.
		CLASS_NAME,             // 視窗類別
		L"Reversi",				// 視窗標題
		WS_OVERLAPPEDWINDOW,    // 視窗風格
		0, 0, 50, 50,			// 視窗大小及位置
		NULL,					// Parent 視窗    
		NULL,					// 選單
		hInstance,				// Instance handle
		NULL					// Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	//==== 創建 console 視窗 ====//
	AllocConsole();
	freopen( "CONOUT$", "wb", stdout );

	ShowWindow( hwnd, nCmdShow );

	//intially update the screen
	reversi.updataScreen();

	//play sound
	PlaySound(TEXT("chaos drifters.wav"), NULL, SND_FILENAME | SND_ASYNC);

	//==== 執行訊息迴圈 ====//
	MSG msg = { };
	while ( GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return 0;
}

LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint( hwnd, &ps );
			FillRect( hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			EndPaint( hwnd, &ps );
		}
		return 0;

	case WM_KEYDOWN:
		KeyDownEvent( wParam );
		break;

	case WM_KEYUP:
		KeyUpEvent( wParam );
		break;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam );
}
