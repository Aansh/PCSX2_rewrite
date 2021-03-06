#include "VM/VM.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/VPU/VPU_t.h"
#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/EE/VPU/VU/Types/VUCores_t.h"

VUInterpreter_s::VUInterpreter_s(VM * vm, const int vuCoreIndex) :
	VMSystem_t(vm, vuCoreIndex == 0 ? Context_t::VU0 : Context_t::VU1),
	mVUCoreIndex(vuCoreIndex),
	mVUInstruction(0)
{
	mVUCore = getVM()->getResources()->EE->VPU->VU->VU_CORES[vuCoreIndex];
}

void VUInterpreter_s::initialise()
{
}

int VUInterpreter_s::step(const Event_t & event)
{
	// TODO: Implement.
	return event.mQuantity;
}
