#pragma once

#include "Common/PS2 Types/Registers/Register32_t.h"
#include "Common/PS2 Types/Registers/Register128_t.h"
#include "Common/PS2 Types/Registers/ZeroRegister128_t.h"
#include "Common/PS2 Types/Registers/PCRegister32_t.h"


class R5900_t {
public:
	/*
	The R5900 is the EE Core's CPU. It has been modified from a stock R5900 to include Sony specific instructions (multimedia instructions targeting 128-bit operations etc).
	It uses a little-endian configuration (bit 0 is always the LSB).
	*/
	
	// CPU state implementations.

	/*
	The branch delay slot toggle. If the flag is set to true, next cycle will execute the instruction contained at the address mBranchDelaySlotInstructionPC.
	Use the function provided to set the flag, which will automatically assign the correct branch delay instruction address.
	*/
	bool mIsInBranchDelaySlot;
	u32 mBranchDelaySlotInstructionPC;
	void setBranchDelaySlotInstruction()
	{

		mIsInBranchDelaySlot = true;
		mBranchDelaySlotInstructionPC = PC->getPCValue() + Constants::SIZE_MIPS_INSTRUCTION;

	}

	// Register implementations.

	/*
	The R5900 general purpose registers (GPR's) are 128-bit long.
	The upper 64-bits are only used when specific instructions are run, such as using the EE Core specific multimedia instructions (parallel instructions). Example: PADDB.
	See EE Core Users Manual, pg 60.

	GPR defines the 32 GPR's contained within the R5900.
	This is implemented as an array of register numbers from GPR0 -> GPR31 (which translates to r0 -> r31).

	From the EE Core Users Manual, r0 and r31 are reserved:
	- r0 is the zero register, meaning it is always set to a constant 0. This is subclassed from Register128_t.
	- r31 is the link register used by the link and jump instructions. This is not to be used by other instructions.
	In an 8x4 grid.
	*/
	std::shared_ptr<Register128_t> GPR[32] = {
		std::make_shared<ZeroRegister128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>()
	};

	/*
	The HI and LO registers. See EE Core Users manual, pg 60.
	These registers are used to hold the results of integer multiply and divide operations.
	They are 128-bit long.
	*/
	std::shared_ptr<Register128_t> HI = std::make_shared<Register128_t>();      // The HI register. Divided into 2 64-bit segments: the upper 64-bits (HI1) and the lower 64-bits (HI0).
	std::shared_ptr<Register128_t> LO = std::make_shared<Register128_t>();      // The LO register. Divided into 2 64-bit segments: the upper 64-bits (LO1) and the lower 64-bits (LO0).

	/*
	The Shift Amount (SA) register. See EE Core Users manual, pg 61.
	The SA register is used for holding funnel shift instruction results. See the EE Core instruction QFSRV for more details (SA is only used for this instruction).
	It is a 32-bit register.
	*/
	std::shared_ptr<Register32_t> SA = std::make_shared<Register32_t>();

	/*
	The Program Counter (PC) register. See EE Core Users manual, pg 61.
	The PC has 3 states:
	1) During normal program execution, it will point to the current instruction and then get incremented by 4 when finished to move on to the next instruction.
	2) When a jump or branch instruction is encountered, it will point to the target address.
	3) When an exception occurs, the PC is changed to point to the exception vector address.
	It is a 32-bit register, pointing to a virtual address (NOT a PHYSICAL address! This means you need to use the MMUHandler component to get the proper PS2 physical address.)
	Some convience functions are provided for manipulating this value.
	*/
	std::shared_ptr<PCRegister32_t> PC = std::make_shared<PCRegister32_t>();

}; // class R5900