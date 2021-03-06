#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register16_t.h"

/*
ConstantRegister16_t is used as a register with a constant value. Any writes are discarded, and any reads are the value set at creation.
By default set to all 0.
*/
class ConstantRegister16_t : public Register16_t
{
public:
	ConstantRegister16_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const u16 H = 0);

	/*
	Overwritten write functions that discard any value.
	*/
	void writeByte(const Context_t context, const size_t arrayIndex, const u8 value) override;
	void writeHword(const Context_t context, const u16 value) override;

	/*
	Initialise register (set to do nothing).
	*/
	void initialise() override;
};

