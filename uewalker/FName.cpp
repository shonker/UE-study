#include "FName.hpp"

auto printName(std::string str) -> void {
	std::cout << str << '\n';
}

auto getExeBase() -> uintptr_t {
	return reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
}

auto GetEntrySize(bool bIsWide, DWORD length) -> DWORD {
	if (bIsWide)
	{
		return ((length * 2) + alignof(FNameEntryHeader) + FNameEntryAllocator::Stride - 1) & ~(FNameEntryAllocator::Stride - 1);
	}
	else
	{
		return (length + alignof(FNameEntryHeader) + FNameEntryAllocator::Stride - 1) & ~(FNameEntryAllocator::Stride - 1);
	}
}

auto getFNameEntryAllocator() -> FNameEntryAllocator* {
	const char* moduleName = "AtomicHeart-Win64-Shipping.exe";
	auto offset = 0x5;
	auto address = find_signature(moduleName, "74 09 48 8D 05 ? ? ? ? EB 13") + offset;
	auto rip_offset = *reinterpret_cast<DWORD*>(address);
	FNameEntryAllocator* fNameEntryAllocator = reinterpret_cast<FNameEntryAllocator*>(address + sizeof(DWORD) + rip_offset);
	return fNameEntryAllocator;
}

auto getNameDump() -> void {
	uintptr_t moduleBase = getExeBase();
	FNameEntryAllocator* fNameEntryAllocator = getFNameEntryAllocator();

	for ( short j = 0; j < fNameEntryAllocator->CurrentBlock; ++j ) {
		char* pFNameEntry = reinterpret_cast<char*>(fNameEntryAllocator->Blocks[j]);

		for (int i = 0; i < FNameEntryAllocator::BlockSizeBytes; ++i) {
			DWORD length = reinterpret_cast<FNameEntryHeader*>(pFNameEntry)->Len >> 5;
			bool bIsWide = reinterpret_cast<FNameEntryHeader*>(pFNameEntry)->bIsWide;

			if (length == 0)
				break;

			// creating a buffer
			char tmpName[NAME_SIZE] = { 0, };

			// skipping 0x2 which is the sizeof Header
			strncpy(tmpName, pFNameEntry + 0x2, length);
			printName(std::string(tmpName));
			// clearing it out
			tmpName[length] = 0;

			// moving to the next entry
			pFNameEntry += GetEntrySize(bIsWide, length);
		}
	}
}