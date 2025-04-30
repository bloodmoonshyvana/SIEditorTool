
#include <windows.h>
#include <tchar.h>

#define ID_FILE_EXIT    9001
#define ID_TARGET_FO4   1001
#define ID_TARGET_SKSE  1002
#define ID_TARGET_SKYRIMSE 1003
#define ID_TARGET_MINEJAVA 1004
#define ID_TARGET_MINEBED  1005
#define ID_TARGET_7DTD     1006
#define ID_TARGET_CUSTOM   1007
#define ID_ANIM_IMPORT 3001
#define ID_ANIM_EDIT   3002
#define ID_ANIM_EXPORT 3003

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

        // Datei-Menü
        HMENU hFile = CreatePopupMenu();
        AppendMenu(hFile, MF_STRING, ID_FILE_EXIT, _T("Beenden"));
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, _T("Datei"));

        // Zielplattformen-Menü
        HMENU hTargetMenu = CreatePopupMenu();
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_FO4, _T("Fallout 4"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_SKSE, _T("Skyrim (SKSE)"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_SKYRIMSE, _T("Skyrim SE"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_MINEJAVA, _T("Minecraft Java"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_MINEBED, _T("Minecraft Bedrock"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_7DTD, _T("7 Days to Die"));
        AppendMenu(hTargetMenu, MF_STRING, ID_TARGET_CUSTOM, _T("SchwarzeInversion"));
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hTargetMenu, _T("Ziel-Plattform"));

        // Animationen-Menü
        HMENU hAnimationMenu = CreatePopupMenu();
        AppendMenu(hAnimationMenu, MF_STRING, ID_ANIM_IMPORT, _T("Importieren"));
        AppendMenu(hAnimationMenu, MF_STRING, ID_ANIM_EDIT, _T("Bearbeiten"));
        AppendMenu(hAnimationMenu, MF_STRING, ID_ANIM_EXPORT, _T("Exportieren"));
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hAnimationMenu, _T("Animation"));

        SetMenu(hWnd, hMenubar);
        break;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_FILE_EXIT:
            PostQuitMessage(0);
            break;
        case ID_ANIM_IMPORT:
            MessageBox(hWnd, _T("Animations-Import wird vorbereitet..."), _T("Animation"), MB_OK);
            break;
        case ID_ANIM_EDIT:
            MessageBox(hWnd, _T("Animationen bearbeiten..."), _T("Animation"), MB_OK);
            break;
        case ID_ANIM_EXPORT:
            MessageBox(hWnd, _T("Animation wird exportiert..."), _T("Animation"), MB_OK);
            break;
        case ID_TARGET_FO4:
        case ID_TARGET_SKSE:
        case ID_TARGET_SKYRIMSE:
        case ID_TARGET_MINEJAVA:
        case ID_TARGET_MINEBED:
        case ID_TARGET_7DTD:
        case ID_TARGET_CUSTOM:
            MessageBox(hWnd, _T("Zielplattform wurde gewählt."), _T("Plattform"), MB_OK);
            break;
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
