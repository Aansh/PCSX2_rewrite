#include "Common/Types/Register/BitfieldRegister32_t.h"

#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPCoreCOP0Register_Context_t::IOPCoreCOP0Register_Context_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::BadVPN2, "BadVPN2", 2, 19, 0);
	registerField(Fields::PTEBase, "PTEBase", 21, 11, 0);
}

IOPCoreCOP0Register_Status_t::IOPCoreCOP0Register_Status_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::IEc, "IEc", 0, 1, 0);
	registerField(Fields::KUc, "KUc", 1, 1, 0);
	registerField(Fields::IEp, "IEp", 2, 1, 0);
	registerField(Fields::KUp, "KUp", 3, 1, 0);
	registerField(Fields::IEo, "IEo", 4, 1, 0);
	registerField(Fields::KUo, "KUo", 5, 1, 0);
	registerField(Fields::IM, "IM", 8, 8, 0);
	registerField(Fields::IsC, "IsC", 16, 1, 0);
	registerField(Fields::SwC, "SwC", 17, 1, 0);
	registerField(Fields::PZ, "PZ", 18, 1, 0);
	registerField(Fields::CM, "CM", 19, 1, 0);
	registerField(Fields::PE, "PE", 20, 1, 0);
	registerField(Fields::TS, "TS", 21, 1, 0);
	registerField(Fields::BEV, "BEV", 22, 1, 1);
	registerField(Fields::RE, "RE", 25, 1, 0);
	registerField(Fields::CU, "CU", 28, 4, 0);
}

void IOPCoreCOP0Register_Status_t::pushExceptionStack(const Context_t context)
{
	// New status = shift (KU|IP)(c|p) bits left by 2 then make (KU|IP)c bits = 0.
	u32 statusValue = readWord(context);
	writeWord(context, (statusValue & (~0x3F)) | ((statusValue & 0xF) << 2));
}

void IOPCoreCOP0Register_Status_t::popExceptionStack(const Context_t context)
{
	// New status = shift (KU|IP)(p|o) bits right by 2. Leave old bits unchanged after.
	u32 statusValue = readWord(context);
	writeWord(context, (statusValue & (~0xF)) | ((statusValue & 0x3C) >> 2));
}

bool IOPCoreCOP0Register_Status_t::isExceptionsMasked(const Context_t context)
{
	return false;
}

bool IOPCoreCOP0Register_Status_t::isInterruptsMasked(const Context_t context)
{
	return !(getFieldValue(context, Fields::IEc) > 0);
}

bool IOPCoreCOP0Register_Status_t::isIRQMasked(const Context_t context, const int irq)
{
	return !((getFieldValue(context, Fields::IM) & (1 << irq)) > 0);
}

IOPCoreCOP0Register_Cause_t::IOPCoreCOP0Register_Cause_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::ExcCode, "ExcCode", 2, 5, 0);
	registerField(Fields::IP, "IP", 8, 8, 0);
	registerField(Fields::CE, "CE", 28, 2, 0);
	registerField(Fields::BD, "BD", 31, 1, 0);
}

void IOPCoreCOP0Register_Cause_t::clearIP(const Context_t context)
{
	setFieldValue(context, Fields::IP, 0);
}

void IOPCoreCOP0Register_Cause_t::setIRQLine(const Context_t context, const int irq)
{
	auto temp = getFieldValue(context, Fields::IP) | (1 << irq);
	setFieldValue(context, Fields::IP, temp);
}

void IOPCoreCOP0Register_Cause_t::clearIRQLine(const Context_t context, const int irq)
{
	auto temp = (getFieldValue(context, Fields::IP) & (~(1 << irq))) & 0xFF; // 0xFF mask to strip off any other bits as a safety precaution.
	setFieldValue(context, Fields::IP, temp);
}

IOPCoreCOP0Register_PRId_t::IOPCoreCOP0Register_PRId_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::Rev, "Rev", 0, 8, 0x1F); // Same as old PCSX2.
	registerField(Fields::Imp, "Imp", 8, 8, 0x00);
}
