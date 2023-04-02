#include "UObject.hpp"

using namespace std;

auto GetTUObjectArray() -> TUObjectArray {
	const char* moduleName = "AtomicHeart-Win64-Shipping.exe";
	auto offset = 0x2;
	auto address = find_signature( moduleName, "89 15 ? ? ? ? 85 FF" ) + offset;
	auto rip_offset = *reinterpret_cast< DWORD* >( address );
	FUObjectArray* fUObjectArray = reinterpret_cast< FUObjectArray* >( address + sizeof( DWORD ) + rip_offset );
	cout << "fUObjectArray: " << hex << (uintptr_t)fUObjectArray << endl;
	return fUObjectArray->ObjObjects;
}

FORCEINLINE auto FChunkedFixedUObjectArray::GetObjectPtr( int32_t Index ) -> FUObjectItem* {
	const int32_t ChunkIndex = Index / NumElementsPerChunk;
	const int32_t WithinChunkIndex = Index % NumElementsPerChunk;
	if ( !IsValidIndex( Index ) ) return nullptr;
	if ( !( ChunkIndex < NumChunks ) ) return nullptr;
	if ( !( Index < MaxElements ) ) return nullptr;
	FUObjectItem* Chunk = Objects[ ChunkIndex ];
	if ( !Chunk ) return nullptr;
	return Chunk + WithinChunkIndex;
}

FORCEINLINE auto FChunkedFixedUObjectArray::IsValidIndex( int32_t Index ) -> bool {
	return Index < NumElements && Index >= 0;
}

auto UObject::GetFullName() {
	UObject* ClassObj = this->ClassPrivate;
	UObject* OuterObj = this->OuterPrivate;
	DWORD NameIndex = ClassObj->NamePrivate.ComparisonIndex;
	cout << "NameIndex: " << NameIndex << endl;
}

auto GetObjects() -> void {
	TUObjectArray tUObject = GetTUObjectArray();
	for ( int i = 1; i < tUObject.NumElements; ++i ) {
		FUObjectItem* object = tUObject.GetObjectPtr( i );
		if (object) {
			object->Object->GetFullName();
		}
		else {
			cout << i << "is null" << endl;
		}
	}
}
