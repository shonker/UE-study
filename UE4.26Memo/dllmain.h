#pragma once

#include <iostream>
#include <Windows.h>
#include <Psapi.h>

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

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
	int64_t Lock;
	int32_t CurrentBlock;
	int32_t CurrentByCursor;
	PVOID Blocks[FNameMaxBlocks];
};

