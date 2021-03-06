#include <algorithm>

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/Register/Register32_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter_s::PMAXH()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		s16 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns parameter 0 if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->writeHword(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PMAXW()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), i));
		s32 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns parameter 0 if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->writeWord(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PMINH()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		s16 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns parameter 0 if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->writeHword(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PMINW()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), i));
		s32 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns parameter 0 if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->writeWord(getContext(), i, result);
	}
}

void EECoreInterpreter_s::MAX_S()
{
	// Fd = MAX(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
		return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	CSR->clearFlags(getContext());
	f32 source1Val = source1Reg->readFloat(getContext());
	f32 source2Val = source2Reg->readFloat(getContext());
	f32 result = (source1Val >= source2Val) ? source1Val : source2Val; // Dont have to check for valid float as should already be valid from before.
	destReg->writeFloat(getContext(),result);
}

void EECoreInterpreter_s::MIN_S()
{
	// Fd = MIN(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
		return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	CSR->clearFlags(getContext());
	f32 source1Val = source1Reg->readFloat(getContext());
	f32 source2Val = source2Reg->readFloat(getContext());
	f32 result = (source1Val <= source2Val) ? source1Val : source2Val; // Dont have to check for valid float as should already be valid from before.
	destReg->writeFloat(getContext(),result);
}

