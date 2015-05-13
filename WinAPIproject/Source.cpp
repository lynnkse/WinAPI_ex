#include <windows.h>
#include "resource.h"
// Store handles to the main window and application
// instance globally.
HWND ghMainWnd = 0;
HWND secondWnd = 0;
HWND thirdWnd = 0;
HINSTANCE ghAppInst = 0;
// Step 1: Define and implement the window procedures.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// Handle left mouse button click message.
	case WM_LBUTTONDOWN:
		MessageBox(ghMainWnd, L"You clicked the first window", L"Msg", MB_OK);
		return 0;
		// Handle key down message.
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			int ms = MessageBox(ghMainWnd, L"Exit?", L"Msg", MB_YESNO);
			if (ms == 6)
				DestroyWindow(ghMainWnd);
		}
		return 0;
		// Handle destroy window message.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	// Forward any other messages we didn't handle to the
	// default window procedure.
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK scndWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(secondWnd, L"You clicked on the second window", L"Msg", MB_OK);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK thirdWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(thirdWnd, L"You clicked on the third window", L"Msg", MB_OK);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
// WinMain: Entry point for a Windows application.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR cmdLine, int showCmd)
{
	// Save handle to application instance.
	ghAppInst = hInstance;
	
	//creating a blue brush
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(0, 0, 255);
	HBRUSH blueBrush = CreateBrushIndirect(&lb);
	
	// Step 2: Fill out a WNDCLASS instances.
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = ghAppInst;
	wc.hIcon = ::LoadIcon(ghAppInst, MAKEINTRESOURCE(IDI_ICON2));
	wc.hCursor = ::LoadCursor(0, IDC_CROSS);
	//wc.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wc.hbrBackground = blueBrush;
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MyWndClassName";
	
	WNDCLASS wc2;
	wc2.style = CS_HREDRAW | CS_VREDRAW;
	wc2.lpfnWndProc = scndWndProc;
	wc2.cbClsExtra = 0;
	wc2.cbWndExtra = 0;
	wc2.hInstance = ghAppInst;
	wc2.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc2.hCursor = ::LoadCursor(0, IDC_HAND);
	wc2.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wc2.lpszMenuName = 0;
	wc2.lpszClassName = L"MyWndClassName2";
	
	WNDCLASS wc3;
	wc3.style = CS_HREDRAW | CS_VREDRAW;
	wc3.lpfnWndProc = thirdWndProc;
	wc3.cbClsExtra = 0;
	wc3.cbWndExtra = 0;
	wc3.hInstance = ghAppInst;
	wc3.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc3.hCursor = ::LoadCursor(0, IDC_HELP);
	wc3.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wc3.lpszMenuName = 0;
	wc3.lpszClassName = L"MyWndClassName3";
	// Step 3: Register the WNDCLASS instance with Windows.
	RegisterClass(&wc);
	RegisterClass(&wc2);
	RegisterClass(&wc3);
	// Step 4: Create the windows, and save handle in globla
	// window handle variable ghMainWnd.
	ghMainWnd = ::CreateWindow(L"MyWndClassName", L"MyWindow", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 0, 0, 500, 500, 0, 0, ghAppInst, 0);
	if (ghMainWnd == 0)
	{
		::MessageBox(0, L"CreateWindow - Failed", 0, 0);
		return false;
	}
	
	secondWnd = ::CreateWindow(L"MyWndClassName2", L"MyWindow2", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 550, 0, 500, 500, 0, 0, ghAppInst, 0);
	if (secondWnd == 0)
	{
		::MessageBox(0, L"CreateWindow(2) - Failed", 0, 0);
		return false;
	}

	thirdWnd = ::CreateWindow(L"MyWndClassName3", L"MyWindow3", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 550, 0, 250, 250, 0, 0, ghAppInst, 0);
	if (thirdWnd == 0)
	{
		::MessageBox(0, L"CreateWindow(3) - Failed", 0, 0);
		return false;
	}
	// Step 5: Show and update the windows.
	ShowWindow(ghMainWnd, showCmd);
	UpdateWindow(ghMainWnd);
	
	ShowWindow(secondWnd, showCmd);
	UpdateWindow(secondWnd);
	
	ShowWindow(thirdWnd, showCmd);
	UpdateWindow(thirdWnd);
	// Step 6: Enter the message loop and don't quit until
	// a WM_QUIT message is received.
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	// Return exit code back to operating system.
	return (int)msg.wParam;
}