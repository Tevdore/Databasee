#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <data1.c>

int __stdcall WinMain (HINSTANCE h, HINSTANCE h1, char *cmd, int mode)
{
WNDCLASS wc={0};
MSG msg;
HWND hwnd;

wc.hbrBackground=CreateSolidBrush(RGB(0,100,100));
wc.lpfnWndProc=(WNDPROC)proc_main_wnd; //wc.lpfnWndProc=DefWindowProc;
wc.lpszClassName="AA123";	

	if(!RegisterClass(&wc))
	{
	UINT er=GetLastError();
	return 1;
	}


hwnd=CreateWindow("AA123",cmd
				   ,WS_VISIBLE|WS_OVERLAPPEDWINDOW
				   |WS_BORDER
				   |WS_THICKFRAME
				   ,100,100,640,400,0,0,0,0);
while(1)
{
GetMessage(&msg,hwnd,0,0);
TranslateMessage(&msg);
DispatchMessage(&msg);
}
}	
