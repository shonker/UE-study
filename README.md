# uewalker

This repo is to dissect and understand how UE-made game is structured.

Its unlikely that I'll make this a dumper cuz dumper have to deal with every versions of UE, and occasionally games even modify UE to make it hard to auto-dump.

Code is quite messy I was kinda brain storming while coding so my thinking processes are scattered around the code.

1. FName retrieval
2. UObject retrieval
3. get UProperty and Base
4. compare those and get full info
5. profit

# class location

Locations of known classes.

format
- CLASSNAME[A.K.A]: `.h and .cpp`

---

- FChunkedFixedUObjectArray[TUObjectArray]: `Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectArray.h`
- UObject: `Engine\Source\Runtime\CoreUObject\Public\UObject\Object.h`
- UObjectBaseUtility(GetFullName): `Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectBaseUtility.h`, `\Private\UObject\UObjectBaseUtility.h`
- FName(FNameEntry, FNameEntryHeader): `Engine\Source\Runtime\Core\Public\UObject\NameTypes.h`
- FNameEntryAllocator: `Engine\Source\Runtime\Core\Private\UObject\UnrealNames.cpp`
- UEnum(GetNameByIndex): `Engine\Source\Runtime\CoreUObject\Public\UObject\Class.h`, `Engine\Source\Runtime\CoreUObject\Private\UObject\Enum.cpp`
