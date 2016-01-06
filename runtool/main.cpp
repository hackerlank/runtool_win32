/*------------------------------------------------------------------------
HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
(c) Charles Petzold, 1998
-----------------------------------------------------------------------*/



#include <windows.h>
#include <windowsx.h>
#include <Winuser.h>
#include <tchar.h>


#pragma comment(lib,"user32.lib")

HINSTANCE g_hInstance;//全局实例句柄
static TCHAR g_szAppName[] = TEXT("HelloWin");
static TCHAR g_szWinTitle[] = TEXT("The Hello Program");

#define IDB_ONE		3301
#define IDB_TWO		3302
#define IDB_THREE	3303
#define IDB_EDIT1	3304

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	g_hInstance = hInstance;

	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = g_szAppName;
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			g_szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(g_szAppName, // window class name
		g_szWinTitle, // window caption
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT, // initial x position
		CW_USEDEFAULT, // initial y position
		CW_USEDEFAULT, // initial x size
		CW_USEDEFAULT, // initial y size
		NULL, // parent window handle
		NULL, // window menu handle
		hInstance, // program instance handle
		NULL); // creation parameters
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	HWND hButton1,hButton2,hEdit1;
	switch (message)
	{
	case WM_CREATE:
		//PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		//httpget(TEXT("http://172.16.1.100:5360/token.php?s=1"));
		hButton1 = CreateWindow(TEXT("Button"), TEXT("有种就来点击我！"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			35, 45, 160, 65, hwnd, (HMENU)IDB_ONE, g_hInstance, NULL);
		hButton2 = CreateWindow(TEXT("Button"), TEXT("有种就来点击我！"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			35 + 160, 45, 160, 65, hwnd, (HMENU)IDB_TWO, g_hInstance, NULL);
		//hButton3 = CreateWindowEx(TEXT("Button"), TEXT("有种就来点击我！"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			//35 + 160, 45, 160, 65, hwnd, (HMENU)IDB_TWO, g_hInstance, NULL);
		hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("Edit Control"), WS_CHILD | WS_VISIBLE | ES_LEFT, 200, 180, 100, 20, hwnd, (HMENU)IDB_EDIT1, g_hInstance, NULL);
		//SendMessage(edit3, WM_SETFONT, (WPARAM)GetStockObject(17), 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("Hello, Windows!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDB_ONE:
			MessageBox(hwnd, TEXT("您点击了第一个按钮。"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
			break;
		case IDB_TWO:
			MessageBox(hwnd, TEXT("您点击了第二个按钮。"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
			break;
		case IDB_THREE:
			MessageBox(hwnd, TEXT("您点击了第三个按钮。"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
			break;
		case IDB_EDIT1:
			//
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				MessageBox(hwnd, TEXT("您点击了Edit"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
