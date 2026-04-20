#include <windows.h>

#define BUTTON_ID 1

// Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hButton;

    switch (uMsg) {

    case WM_CREATE:
        // Create a button
        hButton = CreateWindow(
            L"BUTTON",                    // Predefined class
            L"Click Me",                  // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            100, 150, 120, 40,            // Position and size
            hwnd,                         // Parent window
            (HMENU)BUTTON_ID,             // Button ID
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
        );
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == BUTTON_ID) {
            MessageBox(hwnd, L"Hello Rituraj!", L"Info", MB_OK);
        }
        return 0;

    //case WM_PAINT:
    //{
    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(hwnd, &ps);

    //    // Fill background
    //    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    //    // Draw text
    //    const wchar_t* text = L"Hello Rituraj";
    //    TextOut(hdc, 100, 100, text, lstrlen(text));

    //    EndPaint(hwnd, &ps);
    //    return 0;
    //}

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Entry Point
int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    const wchar_t CLASS_NAME[] = L"MyWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Auto background

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"My First Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}