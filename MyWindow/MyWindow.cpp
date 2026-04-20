#include <windows.h>

// Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Draw text
        const wchar_t* text = L"Hello Rituraj";
        TextOut(hdc, 100, 100, text, lstrlen(text));

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Entry Point
int main() {
    // Get instance handle
    HINSTANCE hInstance = GetModuleHandle(NULL);

    const wchar_t CLASS_NAME[] = L"MyWindowClass";

    // Register Window Class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc)) {
        return 0;
    }

    // Create Window
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

    // Check if creation failed
    if (hwnd == NULL) {
        return 0;
    }

    // Show Window
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Message Loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}