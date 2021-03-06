#include "Common/Tables/SPU2CoreTable.h"

#include "Resources/SPU2/Types/SPU2Cores_t.h"

constexpr SPU2CoreTable::SPU2CoreInfo_t SPU2CoreTable::SPU2_CORE_TABLE[Constants::SPU2::NUMBER_CORES];

const SPU2CoreTable::SPU2CoreInfo_t * SPU2CoreTable::getInfo(const SPU2Core_t * channel)
{
	return &SPU2_CORE_TABLE[channel->getCoreID()];
}