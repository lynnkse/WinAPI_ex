#include <windows.h>
// Store handles to the main window and application
// instance globally.
HWND ghMainWnd = 0;
HINSTANCE ghAppInst = 0;
// Step 1: Define and implement the window procedure.
LRESULT CALLBACK
WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// Handle left mouse button click message.
	case WM_LBUTTONDOWN:
		MessageBox(0, L"WM_LBUTTONDOWN message.", L"Msg", MB_OK);
		return 0;
		// Handle key down message.
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(ghMainWnd);
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

// WinMain: Entry point for a Windows application.
int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
PSTR cmdLine, int showCmd)
{
	// Save handle to application instance.
	ghAppInst = hInstance;
	// Step 2: Fill out a WNDCLASS instance.
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = ghAppInst;
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = ::LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MyWndClassName";
	// Step 3: Register the WNDCLASS instance with Windows.
	RegisterClass(&wc);
	// Step 4: Create the window, and save handle in globla
	// window handle variable ghMainWnd.
	ghMainWnd = ::CreateWindow(L"MyWndClassName", L"MyWindow", WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, 0, 0, ghAppInst, 0);
	if (ghMainWnd == 0)
	{
		::MessageBox(0, L"CreateWindow - Failed", 0, 0);
		return false;
	}
	// Step 5: Show and update the window.
	ShowWindow(ghMainWnd, showCmd);
	UpdateWindow(ghMainWnd);
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