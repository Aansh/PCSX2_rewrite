#include "stdafx.h"

#include "Common/Types/Registers/LinkRegister128_t.h"
#include "Common/Types/Registers/PCRegister32_t.h"

LinkRegister128_t::LinkRegister128_t(const std::shared_ptr<PCRegister32_t> & pcRegister) :
	mPCRegister(pcRegister)
{
}

void LinkRegister128_t::setLinkAddress()
{
	writeDwordU(0, mPCRegister->getPCValue() + 8);
}