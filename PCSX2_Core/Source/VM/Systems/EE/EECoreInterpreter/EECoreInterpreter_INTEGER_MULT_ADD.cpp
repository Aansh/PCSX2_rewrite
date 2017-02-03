#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register128_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"

void EECoreInterpreter::MADD()
{
	// (LO, HI, Rd) = (HI || LO) + SignExtend<s64>(Rs[SW] * Rt[SW])
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	auto source1Val = static_cast<s32>(source1Reg->readWord(EE, 0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(EE, 0));
	auto loVal = static_cast<s64>(static_cast<s32>(LO->readWord(EE, 0)));
	auto hiVal = static_cast<s64>(static_cast<s32>(HI->readWord(EE, 0)));
	s64 result = (hiVal << 32 | loVal) + (source1Val * source2Val);

	LO->writeDword(EE, 0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
	HI->writeDword(EE, 0, static_cast<s64>(static_cast<s32>(result >> 32)));
	destReg->writeDword(EE, 0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
}

void EECoreInterpreter::MADD1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MADD();
}

void EECoreInterpreter::MADDU()
{
	// (LO, HI, Rd) = (HI || LO) + SignExtend<u64>(Rs[UW] * Rt[UW])
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	auto source1Val = static_cast<u32>(source1Reg->readWord(EE, 0));
	auto source2Val = static_cast<u32>(source2Reg->readWord(EE, 0));
	auto loVal = static_cast<u64>(static_cast<u32>(LO->readWord(EE, 0)));
	auto hiVal = static_cast<u64>(static_cast<u32>(HI->readWord(EE, 0)));
	u64 result = (hiVal << 32 | loVal) + (source1Val * source2Val);

	LO->writeDword(EE, 0, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
	HI->writeDword(EE, 0, static_cast<u64>(static_cast<u32>(result >> 32)));
	destReg->writeDword(EE, 0, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
}

void EECoreInterpreter::MADDU1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MADDU();
}

void EECoreInterpreter::PHMADH()
{
	// (LO, HI, Rd)[i] = SignExtend<s32>(Rs[SH] * Rt[SH])[i] + SignExtend<s32>(Rs[SH] * Rt[SH])[i + 1]
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		auto source1Val1 = static_cast<s16>(source1Reg->readHword(EE, i));
		auto source2Val1 = static_cast<s16>(source2Reg->readHword(EE, i));
		auto source1Val2 = static_cast<s16>(source1Reg->readHword(EE, i + 1));
		auto source2Val2 = static_cast<s16>(source2Reg->readHword(EE, i + 1));
		s32 result = (source1Val2 * source2Val2) + (source1Val1 * source2Val1);

		// Store in LO on i % 4 == 0 (every second loop), else store in HI, at word indexes 0 and 2.
		if (i % 4 == 0)
			LO->writeWord(EE, (i / 4) * 2, result);
		else
			HI->writeWord(EE, ((i - 2) / 4) * 2, result);

		// Set Rd (always done on each loop).
		destReg->writeWord(EE, i / 2, result);
	}
}

void EECoreInterpreter::PHMSBH()
{
	// (LO, HI, Rd)[i] = SignExtend<s32>(Rs[SH] * Rt[SH])[i] - SignExtend<s32>(Rs[SH] * Rt[SH])[i + 1]
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		auto source1Val1 = static_cast<s16>(source1Reg->readHword(EE, i));
		auto source2Val1 = static_cast<s16>(source2Reg->readHword(EE, i));
		auto source1Val2 = static_cast<s16>(source1Reg->readHword(EE, i + 1));
		auto source2Val2 = static_cast<s16>(source2Reg->readHword(EE, i + 1));
		s32 result = (source1Val2 * source2Val2) - (source1Val1 * source2Val1);

		// Store in LO on i % 4 == 0 (every second loop), else store in HI, at word indexes 0 and 2.
		if (i % 4 == 0)
			LO->writeWord(EE, (i / 4) * 2, result);
		else
			HI->writeWord(EE, ((i - 2) / 4) * 2, result);

		// Set Rd (always done on each loop).
		destReg->writeWord(EE, i / 2, result);
	}
}

void EECoreInterpreter::PMADDH()
{
	// (LO, HI, Rd) = SignExtend<s32>(Rs[SH] * Rt[SH] + (HI,LO)[i]) (varying indexes - see EE Core Instruction Manual page 216).
	// (HI,LO)[i] = "C" in comments written below.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()]; // "A"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()]; // "B"
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(EE, i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(EE, i));
		s32 result = source1Val * source2Val;

		if ((i / 2) % 2 == 0)
		{
			auto index = ((i / 2 > 0) ? i - 2 : i); // A0xB0 + C0, A1xB1 + C1, A4xB4 + C4, A5xB5 + C5. Array ternary operator is to select the correct index from 0 -> 3.
			result = result + static_cast<s32>(LO->readWord(EE, index)); 
			LO->writeWord(EE, index, result);
		}
		else
		{
			auto index = ((i / 2 > 1) ? i - 4 : i - 2); // A2xB2 + C2, A3xB3 + C3, A6xB6 + C6, A7xB7 + C7. Array ternary operator is to select the correct index from 0 -> 3.
			result = result + static_cast<s32>(HI->readWord(EE, index));
			HI->writeWord(EE, index, result);
		}
			
		if (i % 2 == 0)
			destReg->writeWord(EE, i / 2, result); // Write to Rd for even indexes. A0xB0 + C0, A2xB2 + C2, A4xB4 + C4, A6xB6 + C6.
	}
}

void EECoreInterpreter::PMADDUW()
{
	// (LO, HI, Rd) = SignExtend<u64>(Rs[UW] * Rt[UW] + (HI || LO)[i]) (varying indexes - see EE Core Instruction Manual page 218).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<u32>(source1Reg->readWord(EE, i));
		auto source2Val = static_cast<u32>(source2Reg->readWord(EE, i));
		auto loVal = static_cast<u64>(static_cast<u32>(LO->readWord(EE, i)));
		auto hiVal = static_cast<u64>(static_cast<u32>(HI->readWord(EE, i)));
		u64 result = (hiVal << 32 | loVal) + (source1Val * source2Val);

		LO->writeDword(EE, i / 2, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
		HI->writeDword(EE, i / 2, static_cast<u64>(static_cast<u32>(result >> 32)));
		destReg->writeDword(EE, i / 2, result);
	}
}

void EECoreInterpreter::PMADDW()
{
	// (LO, HI, Rd) = SignExtend<s64>(Rs[SW] * Rt[SW] + (HI || LO)[i]) (varying indexes - see EE Core Instruction Manual page 220).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(EE, i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(EE, i));
		auto loVal = static_cast<s64>(static_cast<s32>(LO->readWord(EE, i)));
		auto hiVal = static_cast<s64>(static_cast<s32>(HI->readWord(EE, i)));
		s64 result = (hiVal << 32 | loVal) + (source1Val * source2Val);

		LO->writeDword(EE, i / 2, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
		HI->writeDword(EE, i / 2, static_cast<s64>(static_cast<s32>(result >> 32)));
		destReg->writeDword(EE, i / 2, result);
	}
}

void EECoreInterpreter::PMSUBH()
{
	// (LO, HI, Rd) = SignExtend<s32>((HI,LO)[i] - Rs[SH] * Rt[SH]) (varying indexes - see EE Core Instruction Manual page 216).
	// (HI,LO)[i] = "C" in comments written below.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()]; // "A"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()]; // "B"
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(EE, i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(EE, i));
		s32 result = source1Val * source2Val;

		if ((i / 2) % 2 == 0)
		{
			auto index = ((i / 2 > 0) ? i - 2 : i); // C0 - A0xB0, C1 - A1xB1, C4 - A4xB4, C5 - A5xB5. Array ternary operator is to select the correct index from 0 -> 3.
			result = static_cast<s32>(LO->readWord(EE, index)) - result;
			LO->writeWord(EE, index, result);
		}
		else
		{
			auto index = ((i / 2 > 1) ? i - 4 : i - 2); // C2 - A2xB2, C3 - A3xB3, C6 - A6xB6, C7 - A7xB7. Array ternary operator is to select the correct index from 0 -> 3.
			result = static_cast<s32>(HI->readWord(EE, index)) - result;
			HI->writeWord(EE, index, result);
		}

		if (i % 2 == 0)
			destReg->writeWord(EE, i / 2, result); // Write to Rd for even indexes. C0 - A0xB0, C2 - A2xB2, C4 - A4xB4, C6 - A6xB6.
	}
}

void EECoreInterpreter::PMSUBW()
{
	// (LO, HI, Rd) = SignExtend<s64>((HI || LO)[i] - Rs[SW] * Rt[SW]) (varying indexes - see EE Core Instruction Manual page 220).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(EE, i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(EE, i));
		auto loVal = static_cast<s64>(static_cast<s32>(LO->readWord(EE, i)));
		auto hiVal = static_cast<s64>(static_cast<s32>(HI->readWord(EE, i)));
		s64 result = (hiVal << 32 | loVal) - (source1Val * source2Val);

		LO->writeDword(EE, i / 2, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
		HI->writeDword(EE, i / 2, static_cast<s64>(static_cast<s32>(result >> 32)));
		destReg->writeDword(EE, i / 2, result);
	}
}