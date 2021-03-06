#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register32_t.h"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

void IOPCoreInterpreter_s::ADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext()));
	
	s32 result = source1Val + source2Val;

	if (handleOverOrUnderflow32(source1Val, source2Val))
        return;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::ADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto imm = mIOPCoreInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->readWord(getContext()));

	s32 result = sourceVal + imm;

	if (handleOverOrUnderflow32(sourceVal, imm))
        return;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::ADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto imm = mIOPCoreInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->readWord(getContext()));

	s32 result = sourceVal + imm;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::ADDU()
{
	// Rd = Rs + Rt
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext()));

	s32 result = source1Val + source2Val;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::SUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext()));

	s32 result = source1Val - source2Val;

	if (handleOverOrUnderflow32(source1Val, source2Val))
        return;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::SUBU()
{
	// Rd = Rs - Rt
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];

	auto source1Val = static_cast<u32>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<u32>(source2Reg->readWord(getContext()));

	u32 result = source1Val - source2Val;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::DIV()
{
	// (LO, HI) = SignExtend<s32>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& LO = mIOPCore->R3000->LO;
	auto& HI = mIOPCore->R3000->HI;

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext()));

	// Check for VALUE_S32_MIN / -1 (special condition).
	if (source1Val == Constants::VALUE_S32_MIN &&
		source2Val == -1)
	{
		LO->writeWord(getContext(), Constants::VALUE_S32_MIN);
		HI->writeWord(getContext(), static_cast<s32>(0));
	}
	// Check for divide by 0, in which case result is undefined (do nothing).
	else if (source2Val == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
	}
	// Else perform normal operation.
	else
	{
		s32 resultQ = source1Val / source2Val;
		s32 resultR = source1Val % source2Val;

		// Quotient.
		LO->writeWord(getContext(), resultQ);

		// Remainder.
		HI->writeWord(getContext(), resultR);
	}
}

void IOPCoreInterpreter_s::DIVU()
{
	// (LO, HI) = SignExtend<u32>(Rs[UW] / Rt[UW])
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& LO = mIOPCore->R3000->LO;
	auto& HI = mIOPCore->R3000->HI;

	auto source1Val = static_cast<u32>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<u32>(source2Reg->readWord(getContext()));

	// Check for divide by 0, in which case result is undefined (do nothing).
	if (source2Val == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
	}
	// Else perform normal operation.
	else
	{
		u32 resultQ = source1Val / source2Val;
		u32 resultR = source1Val % source2Val;

		// Quotient.
		LO->writeWord(getContext(), resultQ);

		// Remainder.
		HI->writeWord(getContext(), resultR);
	}
}

void IOPCoreInterpreter_s::MULT()
{
	// (LO, HI) = SignExtend<s32>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& LO = mIOPCore->R3000->LO;
	auto& HI = mIOPCore->R3000->HI;

	auto source1Val = static_cast<s64>(static_cast<s32>(source1Reg->readWord(getContext())));
	auto source2Val = static_cast<s64>(static_cast<s32>(source2Reg->readWord(getContext())));

	s64 result = source1Val * source2Val;

	LO->writeWord(getContext(), static_cast<s32>(result & 0xFFFFFFFF));
	HI->writeWord(getContext(), static_cast<s32>((result >> 32) & 0xFFFFFFFF));
}

void IOPCoreInterpreter_s::MULTU()
{
	// (LO, HI) = Rs[UW] * Rt[UW]
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& LO = mIOPCore->R3000->LO;
	auto& HI = mIOPCore->R3000->HI;

	auto source1Val = static_cast<u64>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<u64>(source2Reg->readWord(getContext()));

	u64 result = source1Val * source2Val;

	LO->writeWord(getContext(), static_cast<u32>(result & 0xFFFFFFFF));
	HI->writeWord(getContext(), static_cast<u32>((result >> 32) & 0xFFFFFFFF));
}

void IOPCoreInterpreter_s::SLL()
{
	// Rd = SignExtend<s32>(Rt << shamt(0->31)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	u8 shamt = mIOPCoreInstruction.getRShamt();

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) << shamt);
}

void IOPCoreInterpreter_s::SLLV()
{
	// Rd = SignExtend<s32>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	u8 shamt = source2Reg->readByte(getContext(), 0) & 0x1F;

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) << shamt);
}

void IOPCoreInterpreter_s::SRA()
{
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	u8 shamt = mIOPCoreInstruction.getRShamt();

	destReg->writeWord(getContext(), static_cast<s32>(source1Reg->readWord(getContext())) >> shamt);
}

void IOPCoreInterpreter_s::SRAV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	u8 shamt = source2Reg->readByte(getContext(), 0) & 0x1F;

	destReg->writeWord(getContext(), static_cast<s32>(source1Reg->readWord(getContext())) >> shamt);
}

void IOPCoreInterpreter_s::SRL()
{
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	u8 shamt = mIOPCoreInstruction.getRShamt();

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) >> shamt);
}

void IOPCoreInterpreter_s::SRLV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	u8 shamt = source2Reg->readByte(getContext(), 0) & 0x1F;

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) >> shamt);
}

void IOPCoreInterpreter_s::AND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) & source2Reg->readWord(getContext()));
}

void IOPCoreInterpreter_s::ANDI()
{
	// Rd = Rt AND Extended<u32>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	u32 imm = static_cast<u32>(mIOPCoreInstruction.getIImmU());

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) & imm);
}

void IOPCoreInterpreter_s::NOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->writeWord(getContext(), ~(source1Reg->readWord(getContext()) | source2Reg->readWord(getContext())));
}

void IOPCoreInterpreter_s::OR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) | source2Reg->readWord(getContext()));
}

void IOPCoreInterpreter_s::ORI()
{
	// Rd = Rt AND Extended<u32>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	u32 imm = static_cast<u32>(mIOPCoreInstruction.getIImmU());

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) | imm);
}

void IOPCoreInterpreter_s::XOR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) ^ source2Reg->readWord(getContext()));
}

void IOPCoreInterpreter_s::XORI()
{
	// Rd = Rt XOR Extended<u32>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	u32 imm = static_cast<u32>(mIOPCoreInstruction.getIImmU());

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()) ^ imm);
}

void IOPCoreInterpreter_s::SLT()
{
	// Rd = SignExtended<s32>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext()));

	s32 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::SLTI()
{
	// Rd = SignExtended<s32>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto imm = static_cast<s32>(mIOPCoreInstruction.getIImmS());

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));

	s32 result = (source1Val < imm) ? 1 : 0;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::SLTIU()
{
	// Rd = SignExtended<u32>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];

	u32 source1Val = source1Reg->readWord(getContext());
	u32 imm = static_cast<u32>(static_cast<s32>(mIOPCoreInstruction.getIImmS()));

	u32 result = (source1Val < imm) ? 1 : 0;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::SLTU()
{
	// Rd = SignExtended<u32>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	u32 source1Val = source1Reg->readWord(getContext());
	u32 source2Val = source2Reg->readWord(getContext());

	u32 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeWord(getContext(), result);
}

