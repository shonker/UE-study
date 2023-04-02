#include "dllmain.hpp"

void Detach()
{
	FREECONSOLE();
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
	ALLOCCONSOLE();
	//GetNameDump();
	GetObjects();

	while (true)
	{
		if (GetAsyncKeyState(VK_DELETE) & 1) break;
		Sleep(10);
	}
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		HANDLE hThread = CreateThread(nullptr, 0, fMain, hModule, 0, nullptr);
		if (hThread)
		{
			CloseHandle(hThread);
		}
	}
	else if (dwReason == DLL_PROCESS_DETACH && !lpReserved) {
		Detach();
	}
	return TRUE;
}
