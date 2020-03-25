//-----LunarHunter 2020 BruteForceAltF4 Ver 1-----//
#include <iostream>
#include <windows.h>
#include <fstream>
#include <psapi.h>

using namespace std;
void HideConsole() { ::ShowWindow(::GetConsoleWindow(), SW_HIDE); }
void ShowConsole() { ::ShowWindow(::GetConsoleWindow(), SW_SHOW); }
UINT DefaultMsgBoxTypes = MB_ICONERROR | MB_OK | MB_DEFBUTTON1;
void killFocusedWindow() {
	DWORD processID;
	HWND hwnd = GetForegroundWindow();
	cout << GetWindowThreadProcessId(hwnd, &processID) << "\n";

	cout << "Got process ID: " << processID << "\n";
	HANDLE process1 = OpenProcess(PROCESS_ALL_ACCESS, false, processID);;

	TCHAR nameProc[MAX_PATH];
	
	GetProcessImageFileName(process1, nameProc, MAX_PATH);
	cout << nameProc <<"\n";
	string NameProc1 = nameProc;

	//or NameProc1.find("\\SearchUI.exe") != string::npos
	if (NameProc1.find("\\explorer.exe") != string::npos ) { cout << "Program cannot be terminated! In the exclusions list\n";return;}

	int errorcode = TerminateProcess(process1, 1);
	CloseHandle(process1);
	NameProc1.clear();
	cout << errorcode << "BRU\n";
	if (errorcode == 1) {cout << "Terminated Process By ID\n";}
	else if (errorcode == 0) {
		cout << "Termination Failed! Elevated Permissions Could Be Required!\n";
		MessageBox(
			NULL,
			"Termination Failed! Elevated Permissions Could Be Required!",
			"Termination Failure - BruteForceAltF4",
			DefaultMsgBoxTypes
		);
	}
	return;
}

bool FileExist(string path)
{
	ifstream file(path);
	if (file.is_open())
	{return 1;file.close();}
	else{return 0;}
}

int main() {
	bool hidden = true;
	HideConsole();
	//ShowConsole();
	cout << "LunarHunter Brute Force Alt F4 - 2020 Debug Console\n";{}
	//check if settings file exists here, show tos if not there
	if (!FileExist("settings.ini")) {
		cout << "Settings does not exist!\n";
		int msgboxID = MessageBox(
			NULL,
			"Welcome to Brute Force Alt F4!\nThis program allows you to forcefully close programs that aren't closing anytime soon using CTRL+Alt+F4\nIn order to use this program you must agree to the license provided which should be next to the executable. By clicking yes, you agree to be bound by the terms stated in the license. If you don't have the license file or you don't agree to the terms, click no to exit. This message will only appear once.",
			"Info - Brute Force Alt F4",
			MB_ICONINFORMATION | MB_YESNO | MB_DEFBUTTON1
		);

		if (msgboxID == IDYES) {
			ofstream MyFile("settings.ini");
			MyFile.close();
		}
		else {return 0;}

	}
	else {
		//Read if the settings.ini file has debug mode enabled, if so, show the console.
	}
	if (RegisterHotKey(NULL, 1, MOD_ALT | MOD_CONTROL | MOD_NOREPEAT, 0x73) and RegisterHotKey(NULL, 2, MOD_ALT | MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x73)) {cout << "Hotkeys Register Success!\n";}
	else {
		MessageBox(
			NULL,
			"Unable to register hot key! Program cannot continue.\nExiting...",
			"Init Error - BruteForceAltF4",
			DefaultMsgBoxTypes
		);
		return 0;
	}
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		PeekMessage(&msg, 0, 0, 0, 0x0001);
		cout << msg.message << "\n";
		switch (msg.message) {
			case WM_HOTKEY:
				if (msg.wParam == 1) {
					cout << "hotkey id 1 recieved\n";
					killFocusedWindow();
				}
				else if (msg.wParam == 2) {
					cout << "hotkey id 2 recieved\n";
					if (hidden) {ShowConsole();}
					else {HideConsole();}
					hidden = !hidden;
					//settings window maybe?
					//return 0;
				}
		}
		cout << "Recieved HotKey!\n";
		//killFocusedWindow();
	}
}

//This code here was to get the window title but quickly discovered that it was useless. It still works though, so if you want to add it, just simply uncomment it.

//string data; // The data the user has typed will be stored here
//data.resize(GetWindowTextLength(hwnd) + 1, '\0'); // resize the string so iit can contain the text stored in the edit-control.

//GetWindowText(hwnd, LPSTR(data.c_str()), GetWindowTextLength(hwnd) + 1); // Getting the data the user typed
//cout << data << "\n";
