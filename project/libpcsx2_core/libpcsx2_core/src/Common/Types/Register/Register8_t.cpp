#include "Common/Types/Register/Register8_t.h"

Register8_t::Register8_t(const char* mnemonic, bool debugReads, bool debugWrites, const u8 initialisationValue) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	UB(initialisationValue),
	mInitialisationValue(initialisationValue)
{
}

u8 Register8_t::readByte(const Context_t context)
{
#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8, Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), UB);
#else
		log(Debug, "%s: %s Read u8, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), UB);
#endif
	}
#endif

	return UB;
}

void Register8_t::writeByte(const Context_t context, const u8 value)
{
	UB = value;

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8, Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), UB);
#else
		log(Debug, "%s: %s Write u8, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), UB);
#endif
	}
#endif
}

void Register8_t::initialise()
{
	UB = mInitialisationValue;
}
