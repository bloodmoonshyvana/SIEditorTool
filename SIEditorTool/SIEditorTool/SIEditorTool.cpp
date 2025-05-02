#include <windows.h>
#include "LevelEditor.h"
#include <tchar.h>

#define ID_FILE_EXIT        9001
#define ID_TARGET_FO4       1001
#define ID_TARGET_SKSE      1002
#define ID_TARGET_SKYRIMSE  1003
#define ID_TARGET_MINEJAVA  1004
#define ID_TARGET_MINEBED   1005
#define ID_TARGET_7DTD      1006
#define ID_TARGET_CUSTOM    1007
#define ID_ANIM_IMPORT      3001
#define ID_ANIM_EDIT        3002
#define ID_ANIM_EXPORT      3003
#define ID_LEVEL_EDITOR     2001
#define ID_LEVEL_SAVE       2002
#define ID_LEVEL_LOAD       2003

// Globale Instanzen
LevelEditor levelEditor;
int currentTileID = 1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = _T("SIEditorClass");
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, _T("SIEditorClass"), _T("SI Editor Tool"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        HMENU hMenubar = CreateMenu();

        HMENU hFile = CreatePopupMenu();
        AppendMenu(hFile, MF_STRING, ID_FILE_EXIT, _T("Beenden"));
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, _T("Datei"));

        HMENU hTargetMenu = CreatePopupMenu();
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_FO4, _T("Fallout 4"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_SKSE, _T("Skyrim (SKSE)"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_SKYRIMSE, _T("Skyrim SE"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_MINEJAVA, _T("Minecraft Java"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_MINEBED, _T("Minecraft Bedrock"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_7DTD, _T("7 Days to Die"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_CUSTOM, _T("SchwarzeInversion"));
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hTargetMenu, _T("Ziel-Plattform"));

        HMENU hAnimationMenu = CreatePopupMenu();
        AppendMenu(hAnimationMenu, MF_STRING, ID_ANIM_IMPORT, _T("Importieren"));
        AppendMenu(hAnimationMenu, MF_STRING, ID_ANIM_EDIT, _T("Bearbeiten"));
        AppendMenu(hAnimationMenu, MF_STRING, ID_ANIM_EXPORT, _T("Exportieren"));
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hAnimationMenu, _T("Animation"));

        HMENU hLevelMenu = CreatePopupMenu();
        AppendMenu(hLevelMenu, MF_STRING, ID_LEVEL_EDITOR, _T("Editor öffnen"));
        AppendMenu(hLevelMenu, MF_STRING, ID_LEVEL_SAVE, _T("Karte speichern"));
        AppendMenu(hLevelMenu, MF_STRING, ID_LEVEL_LOAD, _T("Karte laden"));
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hLevelMenu, _T("Level-Editor"));

        SetMenu(hWnd, hMenubar);
        break;
    }

    case WM_KEYDOWN:
        if (wParam >= '1' && wParam <= '9') {
            currentTileID = wParam - '0';
        }
        break;

    case WM_LBUTTONDOWN: {
        int x = LOWORD(lParam) / 32;
        int y = HIWORD(lParam) / 32;
        levelEditor.PlaceTile(x, y, currentTileID);
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }

    case WM_RBUTTONDOWN: {
        int x = LOWORD(lParam) / 32;
        int y = HIWORD(lParam) / 32;
        levelEditor.RemoveTile(x, y);
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_FILE_EXIT:
            PostQuitMessage(0);
            break;
        case ID_ANIM_IMPORT:
        case ID_ANIM_EDIT:
        case ID_ANIM_EXPORT:
        case ID_TARGET_FO4:
        case ID_TARGET_SKSE:
        case ID_TARGET_SKYRIMSE:
        case ID_TARGET_MINEJAVA:
        case ID_TARGET_MINEBED:
        case ID_TARGET_7DTD:
        case ID_TARGET_CUSTOM:
            MessageBox(hWnd, _T("Aktion ausgeführt."), _T("Info"), MB_OK);
            break;
        case ID_LEVEL_EDITOR:
            InvalidateRect(hWnd, NULL, TRUE);
            MessageBox(hWnd, _T("Level-Editor geöffnet!"), _T("Editor"), MB_OK);
            break;
        case ID_LEVEL_SAVE:
            levelEditor.SaveMap("map.txt");
            MessageBox(hWnd, _T("Karte gespeichert!"), _T("Editor"), MB_OK);
            break;
        case ID_LEVEL_LOAD:
            levelEditor.LoadMap("map.txt");
            InvalidateRect(hWnd, NULL, TRUE);
            MessageBox(hWnd, _T("Karte geladen!"), _T("Editor"), MB_OK);
            break;
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        levelEditor.DrawEditor(hdc);
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
