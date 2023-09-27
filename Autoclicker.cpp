#include <iostream>
#include <Windows.h>
#include <thread>

void AutoClick(int x, int y, int durationInMilliseconds) {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    SetCursorPos(x, y);

    // Miliseconds
    DWORD startTime = GetTickCount();

    while (true) {
        // Double click
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(100);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

        DWORD currentTime = GetTickCount();
        if (currentTime - startTime >= static_cast<DWORD>(durationInMilliseconds)) {
            break;
        }
    }

    // Return to the original position
    SetCursorPos(cursorPos.x, cursorPos.y);
}


void ShowMousePosition() {
    POINT cursorPos;
    while (true) {
        if (GetAsyncKeyState('X') & 0x8000) {
            // 'X' key is pressed
            GetCursorPos(&cursorPos);

            // Clear the console screen
            system("cls");

            SetConsoleOutputCP(1252);
            std::wcout << L"Mouse position: X = " << cursorPos.x << L", Y = " << cursorPos.y << std::endl;

            std::wcout << L"Do you want to set a click point for autoclicking? (Y/N): ";
            wchar_t response;
            std::wcin >> response;
            std::cin.sync(); // Clear input buffer

            if (response == L'Y' || response == L'y') {
                int clickInterval;

                std::wcout << L"Enter the click interval (in seconds): ";
                float intervalInSeconds;
                std::wcin >> intervalInSeconds;
                std::cin.sync(); // Clear input buffer
                clickInterval = static_cast<int>(intervalInSeconds * 1000); // Convert to milliseconds

                std::wcout << L"Clicking at coordinates: X = " << cursorPos.x << L", Y = " << cursorPos.y << std::endl;
                std::wcout << L"Duration: " << intervalInSeconds << L" seconds" << std::endl;
                std::wcout << L"Program will start soon..." << std::endl;
                Sleep(2000); // Wait for 2 seconds

                // Perform autoclicking at the specified point
                std::wcout << L"Auto-clicking in progress..." << std::endl;
                std::thread clickThread(AutoClick, cursorPos.x, cursorPos.y, clickInterval);
                clickThread.detach();

                Sleep(clickInterval);

                std::wcout << L"Auto-clicking completed." << std::endl;
            }

            system("cls");

            // Restore the console output code page to the default setting
            SetConsoleOutputCP(0);

            // Prevent rapid key presses
            Sleep(100);
        }
        Sleep(10);
    }
}

int main() {
    std::wcout << L"Autoclicker activated. Press 'X' key to display the mouse position." << std::endl;
    ShowMousePosition();
    return 0;
}
