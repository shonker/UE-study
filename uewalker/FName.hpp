#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include "findsignature.hpp"
#include "misc.hpp"

auto PrintName(std::string str) -> void;
auto GetExeBase()->uintptr_t;
auto GetNameDump() -> void;
auto GetEntrySize(bool bIsWide, DWORD length)->DWORD;

class FNameEntryHeader {
public:
	uint16_t bIsWide : 1;
	uint16_t Len : 15;
};

constexpr int NAME_SIZE = 1024;
class FNameEntry
{
public:
	FNameEntryHeader FNameEntryHeader;
	union
	{
		char	AnsiName[NAME_SIZE];
		wchar_t	WideName[NAME_SIZE];
	};
};

static constexpr uint32_t FNameMaxBlockBits = 13;
static constexpr uint32_t FNameMaxBlocks = 1 << FNameMaxBlockBits; // This is how it's defined in UE4.26
class FNameEntryAllocator
{
public:
	enum { Stride = alignof(FNameEntryHeader) };
	enum { BlockSizeBytes = Stride * (1 << 16) };
	int64_t Lock;
	int32_t CurrentBlock;
	int32_t CurrentByCursor;
	PVOID Blocks[FNameMaxBlocks];
};

class FNamePool {
	FNameEntryAllocator Entries;
};

class FName {
	uint32_t ComparisonIndex;
};
