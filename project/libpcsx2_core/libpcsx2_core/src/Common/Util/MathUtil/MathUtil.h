#pragma once

#include "Common/Global/Globals.h"

class MathUtil
{
public:
	/*
	Counts leading bits (1's) from a 32-bit value.
	Example: in 0b1110001..., the answer is 3.
	*/
	static u32 countLeadingBits(s32 value); // Adapted from the old PCSX2 code and Stackoverflow (see inside body). Thanks everyone!

	/*
	Constructs a mask of 1's in a u32 value, starting at bit position startPos with length specified.
	Thanks to: http://www.coranac.com/documents/working-with-bits-and-bitfields/ for code.
	*/
	static u32 constructMask32(int startPos, int length);

	/*
	Extracts a masked value from the given, that starts at maskStartPos and has length maskLength.
	The returned value is shifted right by maskStartPos (ie: becomes its own value).
	*/
	static u32 extractMaskedValue32(u32 value, int maskStartPos, int maskLength);

	/*
	Inserts insertValue into value by shifting it to maskStartPos with length maskLength.
	It will override any bits in the position.
	*/
	static u32 insertMaskedValue32(u32 value, u32 insertValue, int maskStartPos, int maskLength);

	/*
	Constructs a mask of 1's in a u16 value, starting at bit position startPos with length specified.
	Thanks to: http://www.coranac.com/documents/working-with-bits-and-bitfields/ for code.
	*/
	static u16 constructMask16(int startPos, int length);

	/*
	Extracts a masked value from the given, that starts at maskStartPos and has length maskLength.
	The returned value is shifted right by maskStartPos (ie: becomes its own value).
	*/
	static u16 extractMaskedValue16(u16 value, int maskStartPos, int maskLength);

	/*
	Inserts insertValue into value by shifting it to maskStartPos with length maskLength.
	It will override any bits in the position.
	*/
	static u16 insertMaskedValue16(u16 value, u16 insertValue, int maskStartPos, int maskLength);

	/*
	Saturates/clamps values to the next smallest size, if above the maximum value allowed.
	Eg: for 0x02345678 to hword, this becomes 0x7FFF;
	*/
	static s16 saturateWordToHword(s32 value);
	static s32 saturateDwordToWord(s64 value);

	/*
	Finds N by log2(value), when value is known to be 2^N (only works on this condition). Used as a fast lookup instead of normal log2().
	Thanks to: http://graphics.stanford.edu/~seander/bithacks.html
	*/
	static u32 log2N(u32 value);

	/*
	Provided x and y, returns a bool for the condition that addition it will not overflow, and for subtraction it will not underflow.
	User must select the appropriate bit size (ie 32, 64).
	Thanks to http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
	*/
	static bool testOverflow32(s32 x, s32 y);
	static bool testUnderflow32(s32 x, s32 y);
	static bool testOverOrUnderflow32(s32 x, s32 y);
	static bool testOverflow64(s64 x, s64 y);
	static bool testUnderflow64(s64 x, s64 y);
	static bool testOverOrUnderflow64(s64 x, s64 y);

	/*
	Gets the high 19 bits of the 32-bit value parsed, stored at the LSB's of the returned u32.
	*/
	static u32 getHI19(u32 value);
};
