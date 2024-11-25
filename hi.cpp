#include <iostream>
#include <windows.h>
#include <string>
#include <tlhelp32.h>
#include <vector>

void RunTaskSchedulerTask(const std::wstring& taskName) {
    std::wstring command = L"schtasks /run /tn "" + taskName + L""";
    _wsystem(command.c_str());
}

bool IsRobloxGameRunning() {
    HWND hwnd = FindWindow(NULL, L"Roblox");
    if (hwnd == NULL) {
        return false;
    }

    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    return (strstr(windowTitle, "Roblox") != NULL);
}

void RunExecutableMinimized(const std::wstring& exePath) {

    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_MINIMIZE;

    if (CreateProcess(
        exePath.c_str(),
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi)
        ) {

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        std::cerr << "Failed to create process." << std::endl;
    }
}

int main() {
    const std::wstring taskName = L"ilovecloset";
    const std::wstring exePath = L"C:\\Users\\simon\\Downloads\\Build-3.0.8\\Celex.exe";

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    std::cout << "Waiting for Roblox game to launch..." << std::endl;

    while (true) {
        if (IsRobloxGameRunning()) {
            std::cout << "Roblox game is running! Triggering the task..." << std::endl;
            RunTaskSchedulerTask(taskName);
            RunExecutableMinimized(exePath);
            break;
        }
        Sleep(1000);
    }

    return 0;
}