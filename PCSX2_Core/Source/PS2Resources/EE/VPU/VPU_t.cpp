#include "stdafx.h"

#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/VIF/VIF_t.h"
#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/Types/VPURegisters_t.h"

VPU_t::VPU_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	VIF(std::make_shared<VIF_t>(getRootResources())),
	VU(std::make_shared<VU_t>(getRootResources())),
	STAT(std::make_shared<VPURegister_STAT_t>())
{
}