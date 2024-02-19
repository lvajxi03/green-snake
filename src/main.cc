/* Win32 headers */
#include <windows.h>

/* Local headers */
#include "arena.h"
#include "game.h"
#include "res.h"

#include "globals.h"

HINSTANCE instancja = NULL;
HWND okno = NULL;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HACCEL hAccelerators;
	MSG msg;

	instancja = hInstance;

	if (!RegisterMainWindowClass())
	{
		MessageBox(
			NULL,
			TEXT("Error registering main window class."),
			TEXT("Error"),
			MB_ICONERROR | MB_OK);
		return 0;
	}

	if (!(okno = CreateMainWindow()))
	{
		MessageBox(
			NULL,
			TEXT("Error creating main window."),
			TEXT("Error"),
			MB_ICONERROR | MB_OK);
		return 0;
	}

	hAccelerators = LoadAccelerators(
		instancja,
		MAKEINTRESOURCE(IDR_ACCELERATOR));


	ShowWindow(okno, nCmdShow);
	UpdateWindow(okno);

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if (!TranslateAccelerator(okno, hAccelerators, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
