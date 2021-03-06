#pragma once

#include "Common/Types/Memory/ByteMemory_t.h"

/*
Read-only mapped memory, used for eg: the EE BIOS.
Will not write anything when requested, and instead silently discards the data.
You can still load in a file (through readFile()), which is the intended purpose.
*/
class ROByteMemory_t : public ByteMemory_t
{
public:
	ROByteMemory_t(const char * mnemonic, bool debugReads, bool debugWrites, const size_t byteSize);

	/*
	All writes are discarded - this is a silent discard!
	*/
	void writeByte(const Context_t context, const size_t byteOffset, const u8 value) override;
	void writeHword(const Context_t context, const size_t byteOffset, const u16 value) override;
	void writeWord(const Context_t context, const size_t byteOffset, const u32 value) override;
	void writeDword(const Context_t context, const size_t byteOffset, const u64 value) override;
	void writeQword(const Context_t context, const size_t byteOffset, const u128 value) override;
};