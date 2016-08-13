#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Util/MathUtil/MathUtil.h"
#include <climits>

#if defined(ENV_WINDOWS)
 #include <intrin.h>
#elif defined(ENV_UNIX)
 #include <intrin_x86.h>
#else
#endif

u32 MathUtil::countLeadingBits(s32 value)
{
	// If the sign bit is 1, we invert the bits to 0 for count-leading-zero.
	if (value < 0)
		value = ~value;

	// Perform our count leading zero. Formula from here: http://stackoverflow.com/questions/4244274/how-do-i-count-the-number-of-zero-bits-in-an-integer. Thanks!
	u32 num_leading_bits = 0;
	for (u32 i = 0; i < CHAR_BIT * sizeof value; ++i)
	{
		if ((value & (1 << i)) == 0)
			++num_leading_bits;
	}

	return num_leading_bits;
}

s16 MathUtil::saturateWordToHword(s32 value)
{
	if (value > Constants::VALUE_S16_MAX)
		return Constants::VALUE_S16_MAX;
	else if (value < Constants::VALUE_S16_MIN)
		return Constants::VALUE_S16_MIN;
	else 
		return static_cast<s16>(value);
}

s32 MathUtil::saturateDwordToWord(s64 value)
{
	if (value > Constants::VALUE_S32_MAX)
		return Constants::VALUE_S32_MAX;
	else if (value < Constants::VALUE_S32_MIN)
		return Constants::VALUE_S32_MIN;
	else
		return static_cast<s32>(value);
}
