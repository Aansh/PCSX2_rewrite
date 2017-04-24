#pragma once

#include "VM/Types/VMSystem_s.h"

class CDVD_t;

/*
CDVD handler logic.
HLE-ish approach - emulates bios function calls made? There is near no documentation otherwise.
Everything from PCSX2. See CDVD.cpp etc.
*/
class CDVD_s : public VMSystem_s
{
public:
	CDVD_s(VM * vm);
	virtual ~CDVD_s() = default;

	/*
	Initalisation.
	*/
	void initalise() override;

	/*
	Checks the CDVD state for any actions to be performed, and steps through if needed.
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	/*
	Resources.
	*/
	std::shared_ptr<CDVD_t> mCDVD;

	/*
	N Command instructions and table.
	In theory there can be 256 (u8) total instructions, but only a handful of them are implemented.
	*/
	void NCMD_INSTRUCTION_UNKNOWN();
	void(CDVD_s::* NCMD_INSTRUCTION_TABLE[Constants::CDVD::NUMBER_NCMD_INSTRUCTIONS])() =
	{
		/* 0x00 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x01 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x02 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x03 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x04 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x05 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x06 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x07 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x08 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x09 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x10 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x11 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x12 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x13 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x14 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x15 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x16 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x17 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x18 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x19 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x20 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x21 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x22 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x23 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x24 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x25 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x26 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x27 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x28 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x29 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x30 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x31 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x32 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x33 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x34 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x35 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x36 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x37 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x38 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x39 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x40 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x41 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x42 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x43 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x44 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x45 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x46 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x47 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x48 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x49 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x50 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x51 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x52 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x53 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x54 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x55 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x56 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x57 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x58 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x59 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x60 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x61 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x62 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x63 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x64 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x65 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x66 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x67 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x68 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x69 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x70 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x71 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x72 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x73 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x74 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x75 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x76 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x77 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x78 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x79 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x80 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x81 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x82 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x83 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x84 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x85 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x86 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x87 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x88 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x89 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x90 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x91 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x92 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x93 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x94 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x95 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x96 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x97 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x98 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x99 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9A */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9B */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9C */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9D */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9E */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9F */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA0 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA1 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA2 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA3 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA4 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA5 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA6 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA7 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA8 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA9 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAA */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAB */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAC */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAD */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAE */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAF */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB0 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB1 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB2 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB3 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB4 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB5 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB6 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB7 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB8 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB9 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBA */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBB */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBC */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBD */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBE */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBF */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC0 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC1 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC2 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC3 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC4 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC5 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC6 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC7 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC8 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC9 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCA */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCB */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCC */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCD */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCE */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCF */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD0 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD1 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD2 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD3 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD4 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD5 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD6 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD7 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD8 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD9 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDA */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDB */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDC */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDD */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDE */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDF */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE0 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE1 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE2 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE3 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE4 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE5 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE6 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE7 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE8 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE9 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEA */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEB */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEC */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xED */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEE */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEF */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF0 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF1 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF2 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF3 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF4 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF5 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF6 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF7 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF8 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF9 */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFA */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFB */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFC */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFD */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFE */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFF */ &CDVD_s::NCMD_INSTRUCTION_UNKNOWN
	};

	/*
	S Command instructions and table.
	In theory there can be 256 (u8) total instructions, but only a handful of them are implemented.
	Notation: "Mnemonic" (3:1) means 3 parameter bytes in (S_DATA_IN FIFO), 1 result byte out (S_DATA_OUT).
	*/
	void SCMD_INSTRUCTION_UNKNOWN();
	void SCMD_INSTRUCTION_40();      // "sceCdOpenConfig" (3:1).
	void SCMD_INSTRUCTION_41();      // "sceCdReadConfig" (0:16).
	void SCMD_INSTRUCTION_42();      // "sceCdWriteConfig" (16:1).
	void SCMD_INSTRUCTION_43();      // "sceCdCloseConfig" (0:1).
	void(CDVD_s::* SCMD_INSTRUCTION_TABLE[Constants::CDVD::NUMBER_SCMD_INSTRUCTIONS])() =
	{ 
		/* 0x00 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x01 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x02 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x03 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x04 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x05 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x06 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x07 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x08 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x09 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x10 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x11 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x12 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x13 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x14 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x15 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x16 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x17 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x18 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x19 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x20 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x21 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x22 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x23 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x24 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x25 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x26 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x27 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x28 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x29 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x30 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x31 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x32 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x33 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x34 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x35 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x36 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x37 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x38 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x39 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x40 */ &CDVD_s::SCMD_INSTRUCTION_40,
		/* 0x41 */ &CDVD_s::SCMD_INSTRUCTION_41,
		/* 0x42 */ &CDVD_s::SCMD_INSTRUCTION_42,
		/* 0x43 */ &CDVD_s::SCMD_INSTRUCTION_43,
		/* 0x44 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x45 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x46 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x47 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x48 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x49 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x50 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x51 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x52 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x53 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x54 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x55 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x56 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x57 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x58 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x59 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x60 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x61 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x62 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x63 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x64 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x65 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x66 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x67 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x68 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x69 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x70 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x71 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x72 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x73 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x74 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x75 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x76 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x77 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x78 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x79 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x80 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x81 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x82 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x83 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x84 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x85 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x86 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x87 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x88 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x89 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x90 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x91 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x92 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x93 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x94 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x95 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x96 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x97 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x98 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x99 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9A */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9B */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9C */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9D */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9E */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9F */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA0 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA1 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA2 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA3 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA4 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA5 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA6 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA7 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA8 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA9 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAA */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAB */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAC */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAD */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAE */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAF */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB0 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB1 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB2 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB3 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB4 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB5 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB6 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB7 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB8 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB9 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBA */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBB */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBC */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBD */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBE */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBF */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC0 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC1 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC2 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC3 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC4 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC5 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC6 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC7 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC8 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC9 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCA */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCB */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCC */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCD */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCE */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCF */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD0 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD1 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD2 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD3 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD4 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD5 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD6 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD7 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD8 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD9 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDA */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDB */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDC */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDD */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDE */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDF */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE0 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE1 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE2 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE3 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE4 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE5 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE6 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE7 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE8 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE9 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEA */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEB */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEC */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xED */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEE */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEF */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF0 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF1 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF2 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF3 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF4 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF5 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF6 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF7 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF8 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF9 */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFA */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFB */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFC */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFD */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFE */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFF */ &CDVD_s::SCMD_INSTRUCTION_UNKNOWN
	};
};

