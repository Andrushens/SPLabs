// lr3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lr3.h"

#define MAX_LOADSTRING 100
#define BUTTON_CLEAR_ID 1
#define BUTTON_DRAW_ID 2

bool isVisible = false;

HWND hWnd, buttonClear, buttonDraw;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LR3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR3));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   buttonDraw = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
       20, 20, 60, 60, hWnd, (HMENU)BUTTON_DRAW_ID, NULL, NULL);

   buttonClear = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
       100, 20, 60, 60, hWnd, (HMENU)BUTTON_CLEAR_ID, NULL, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case BUTTON_DRAW_ID:
			isVisible = true;
			InvalidateRect(hWnd, NULL, true);
			break;
		case BUTTON_CLEAR_ID:
			isVisible = false;
			InvalidateRect(hWnd, NULL, true);
			break;
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
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* draw = (DRAWITEMSTRUCT*)lParam;
		HBRUSH brush;
		HPEN pen;

		switch (draw->CtlID)
		{
		case BUTTON_DRAW_ID:
		{
			HDC hdc = draw->hDC;

			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(0, 255, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(0, 255, 0));
			}

			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Rectangle(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 20, 30, NULL);
			LineTo(hdc, 40, 30);
			MoveToEx(hdc, 30, 20, NULL);
			LineTo(hdc, 30, 40);
		}
		break;
		case BUTTON_CLEAR_ID:
		{
			HDC hdc = draw->hDC;

			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(0, 0, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(255, 0, 0));
			}
			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Rectangle(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 20, 30, NULL);
			LineTo(hdc, 40, 30);
		}
		break;
		default:
			break;
		}
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (isVisible)
		{
			//Arc(hdc, 70, 100, 100, 300, 100, 100, 100, 300);
			POINT p1[5] = { 100, 300, 100, 100, 200, 100, 200, 200, 100, 200};
			Polygon(hdc, p1, 5);

			Arc(hdc, 300, 70, 400, 300, 300, 70, 400, 70);

			Rectangle(hdc, 500, 100, 520, 300);
			POINT p2[5] = { 520, 100, 600, 150, 600, 250, 520, 300};
			Polygon(hdc, p2, 4);

			MoveToEx(hdc, 800, 100, NULL);
			LineTo(hdc, 700, 100);
			LineTo(hdc, 700, 300);
			LineTo(hdc, 800, 300);
			LineTo(hdc, 800, 220);
			LineTo(hdc, 750, 220);
			LineTo(hdc, 750, 260);
			LineTo(hdc, 780, 260);

			Rectangle(hdc, 900, 100, 920, 300);
			Ellipse(hdc, 920, 80, 1000, 120);
			Ellipse(hdc, 920, 180, 1000, 220);
			Ellipse(hdc, 920, 280, 1000, 320);
		}
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
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
