#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register32_t.h"

Register32_t::Register32_t(const char* mnemonic, bool debugReads, bool debugWrites, const u32 initialisationValue) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	UW(initialisationValue),
	mInitialisationValue(initialisationValue)
{
}

u8 Register32_t::readByte(const Context_t context, const size_t arrayIndex)
{
#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8[%d], Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Read u8[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif

	return UB[arrayIndex];
}

void Register32_t::writeByte(const Context_t context, const size_t arrayIndex, const u8 value)
{
	UB[arrayIndex] = value;

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8[%d], Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Write u8[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif
}

u16 Register32_t::readHword(const Context_t context, const size_t arrayIndex)
{
#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u16[%d], Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Read u16[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif

	return UH[arrayIndex];
}

void Register32_t::writeHword(const Context_t context, const size_t arrayIndex, const u16 value)
{
	UH[arrayIndex] = value;

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u16[%d], Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Write u16[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif
}

u32 Register32_t::readWord(const Context_t context)
{
#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32, Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), UW);
#else
		log(Debug, "%s: %s Read u32, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), UW);
#endif
	}
#endif

	return UW;
}

void Register32_t::writeWord(const Context_t context, const u32 value)
{
	UW = value;

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32, Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), UW);
#else
		log(Debug, "%s: %s Write u32, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), UW);
#endif
	}
#endif
}

f32 Register32_t::readFloat(const Context_t context)
{
#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read f32, Value = %A.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), F);
#else
		log(Debug, "%s: %s Read f32, Value = %F.", SYSTEM_STR[context], mMnemonic.c_str(), F);
#endif
	}
#endif

	return F;
}

void Register32_t::writeFloat(const Context_t context, const f32 value)
{
	F = value;

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write f32, Value = %A.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), F);
#else
		log(Debug, "%s: %s Write f32, Value = %F.", SYSTEM_STR[context], mMnemonic.c_str(), F);
#endif
	}
#endif
}

void Register32_t::initialise()
{
	UW = mInitialisationValue;
}
