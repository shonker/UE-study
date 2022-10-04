#include "dllmain.h"
#include "debug.h"

#include <vector>

#ifdef _DEBUG
#define ALLOCCONSOLE()\
{\
    AllocConsole();\
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);\
}
#define FREECONSOLE()\
{\
    fclose(stdout);\
    FreeConsole();\
}
#else
#define ALLOCCONSOLE()
#define FREECONSOLE()
#endif

void Detach()
{
	FREECONSOLE();
}

// <sampleeee.exe> + offset == pFNameEntryAllocator
DWORD offset = 0x439F140;

DWORD GetEntrySize(bool bIsWide, DWORD length)
{
	if (bIsWide)
	{
		return ((length * 2) + alignof(FNameEntryHeader) + FNameEntryAllocator::Stride - 1) & ~(FNameEntryAllocator::Stride - 1);
	}
	else
	{
		return (length + alignof(FNameEntryHeader) + FNameEntryAllocator::Stride - 1) & ~(FNameEntryAllocator::Stride - 1);
	}
}

void printName(std::string str) {
	std::cout << str << '\n';
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
	ALLOCCONSOLE();
	uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
	FNameEntryAllocator* fNameEntryAllocator = reinterpret_cast<FNameEntryAllocator*>(moduleBase + offset);

	char* pFNameEntry = reinterpret_cast<char*>(fNameEntryAllocator->Blocks[0]);

	// getting 50 names. By the way, 50 is just a random number. I'll eraborate it later.
	for (int i = 0; i < 50; ++i) {
		DWORD length = reinterpret_cast<FNameEntryHeader*>(pFNameEntry)->Len >> 5;
		bool bIsWide = reinterpret_cast<FNameEntryHeader*>(pFNameEntry)->bIsWide;

		if (length == 0)
			break;

		// creating a buffer
		char tmpName[NAME_SIZE] = { 0, };

		PRINTF("%d", reinterpret_cast<FNameEntryHeader*>(pFNameEntry)->bIsWide);
		PRINTF("length: %zd", sizeof(char) * length);

		// skipping 0x2 which is the sizeof Header
		strncpy(tmpName, pFNameEntry + 0x2, length);
		printName(std::string(tmpName));
		// clearing it out
		tmpName[length] = 0;
		std::cout << "[*] the length to skip: " << GetEntrySize(bIsWide, length) << std::endl;
		// std::cout << "[*] the length to skip: " << sizeof(FNameEntryHeader) + sizeof(char) * length << std::endl;

		// moving to the next entry
		pFNameEntry += GetEntrySize(bIsWide, length);
	}

	PUTS("iterate ends");

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
