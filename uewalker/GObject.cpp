#include "GObject.hpp"

using namespace std;

auto getTUObjectArray() -> TUObjectArray {
	const char* moduleName = "AtomicHeart-Win64-Shipping.exe";
	auto offset = 0x2;
	auto address = find_signature(moduleName, "89 15 ? ? ? ? 85 FF") + offset;
	auto rip_offset = *reinterpret_cast<DWORD*>(address);
	FUObjectArray* fUObjectArray = reinterpret_cast<FUObjectArray*>(address + sizeof(DWORD) + rip_offset);
	cout << hex << (uintptr_t)fUObjectArray << endl;
	return fUObjectArray->ObjObjects;
}

auto getObject() -> void {
	TUObjectArray tUObject = getTUObjectArray();
}
