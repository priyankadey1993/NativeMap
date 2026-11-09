// NativeMap.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "NativeMap.h"
#include <windows.h>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
#define MAX_LOADSTRING 100

struct Node {
    int id;
    int x;
    int y;
    wstring name;
};

struct Edge {
    int u, v; // ids of connected nodes
};

vector<Node> cities;
vector<Edge> roads;

void IntializeMapData()
{
    cities = {
        {0, 150, 200, L"City A"},
        {1, 400, 150, L"City B"},
        {2, 650, 350, L"City C"},
        {3, 300, 500, L"City D"},
        {4, 550, 600, L"Main Station"}
    };
    roads= {{0, 1}, {1, 2}, {0, 3}, {3, 2}, {3, 4}, {2, 4}};
       

}

std::vector<int> shortestPathIds = { 0, 3, 2 };

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void        DrawMap(HWND hwnd, HDC hdc);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    IntializeMapData();
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NATIVEMAP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NATIVEMAP));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NATIVEMAP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NATIVEMAP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
 // <-- Yahan size 900, 700 kar dein
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 900, 700, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            DrawMap(hWnd, hdc);
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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

void DrawMap(HWND hwnd, HDC hdc)
{
    HPEN hRoadPen = CreatePen(PS_SOLID, 3, RGB(120, 120, 120));
    HPEN hPathPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
    HBRUSH hCityBrush = CreateSolidBrush(RGB(0, 100, 255));

    HGDIOBJ holdPen = SelectObject(hdc, hRoadPen);
    HGDIOBJ holdBrush = SelectObject(hdc, hCityBrush);

    for (const auto& road : roads)
    {
        MoveToEx(hdc, cities[road.u].x, cities[road.u].y, NULL);
        LineTo(hdc, cities[road.v].x, cities[road.v].y);
    }

    SelectObject(hdc, hPathPen);

    if (shortestPathIds.size() > 1)
    {
        for (size_t i = 0; i < shortestPathIds.size() - 1; ++i)
        {
            MoveToEx(hdc, cities[shortestPathIds[i]].x, cities[shortestPathIds[i]].y, NULL);
            LineTo(hdc, cities[shortestPathIds[i + 1]].x, cities[shortestPathIds[i + 1]].y);
        }
    }
    SelectObject(hdc, holdPen);
    int radius = 10;
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT);

    for (const auto& city : cities) {
        SelectObject(hdc, hCityBrush);
        Ellipse(hdc, city.x - radius, city.y - radius, city.x + radius, city.y + radius);

        SelectObject(hdc, hRoadPen);
        Ellipse(hdc, city.x - radius, city.y - radius, city.x + radius, city.y + radius);
        TextOut(hdc, city.x + 15, city.y - 10, city.name.c_str(), (int)city.name.length());
    }

    // Bottom info box text
    TextOut(hdc, 20, 610, L"Shortest Path: City A -> City D -> Main Station", 47);

    // Cleanup
    SelectObject(hdc, holdPen);
    SelectObject(hdc, holdBrush);
    DeleteObject(hRoadPen);
    DeleteObject(hPathPen);
    DeleteObject(hCityBrush);

}