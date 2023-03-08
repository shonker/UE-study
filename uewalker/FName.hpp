#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include "findsignature.hpp"
#include "debug.hpp"

auto printName(std::string str) -> void;
auto getExeBase()->uintptr_t;
auto getNameDump() -> void;
auto GetEntrySize(bool bIsWide, DWORD length)->DWORD;

class FNameEntryHeader {
public:
	USHORT bIsWide : 1;
	USHORT Len : 15;
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

