#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register16_t.h"
#include "Common/Types/Register/BitfieldRegister16_t.h"
#include "Common/Tables/SPU2CoreTable.h"

/*
The SPU2 Core (Voice) VOL general purpose bitfield register.
*/
class SPU2CoreRegister_VOL_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int ConstValue = 0;
		static constexpr int ConstToggle = 1;
		static constexpr int LinExpMode = 2;
		static constexpr int X = 3;
		static constexpr int LinExpValue = 4;
	};

	SPU2CoreRegister_VOL_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The SPU2 Core "CHAN0" general purpose bitfield register.
*/
class SPU2CoreRegister_CHAN0_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int V0 = 0;
		static constexpr int V1 = 1;
		static constexpr int V2 = 2;
		static constexpr int V3 = 3;
		static constexpr int V4 = 4;
		static constexpr int V5 = 5;
		static constexpr int V6 = 6;
		static constexpr int V7 = 7;
		static constexpr int V8 = 8;
		static constexpr int V9 = 9;
		static constexpr int V10 = 10;
		static constexpr int V11 = 11;
		static constexpr int V12 = 12;
		static constexpr int V13 = 13;
		static constexpr int V14 = 14;
		static constexpr int V15 = 15;
	};

	SPU2CoreRegister_CHAN0_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The SPU2 Core "CHAN1" general purpose bitfield register.
*/
class SPU2CoreRegister_CHAN1_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int V16 = 0;
		static constexpr int V17 = 1;
		static constexpr int V18 = 2;
		static constexpr int V19 = 3;
		static constexpr int V20 = 4;
		static constexpr int V21 = 5;
		static constexpr int V22 = 6;
		static constexpr int V23 = 7;
	};

	SPU2CoreRegister_CHAN1_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The SPU2 Core MMIX register.
*/
class SPU2CoreRegister_MMIX_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int SINER = 0;
		static constexpr int SINEL = 1;
		static constexpr int SINR = 2;
		static constexpr int SINL = 3;
		static constexpr int MINER = 4;
		static constexpr int MINEL = 5;
		static constexpr int MINR = 6;
		static constexpr int MINL = 7;
		static constexpr int MSNDER = 8;
		static constexpr int MSNDEL = 9;
		static constexpr int MSNDR = 10;
		static constexpr int MSNDL = 11;
	};

	SPU2CoreRegister_MMIX_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The SPU2 Core "ATTR" (attributes) register.
Contains the DMA transfer state parameters, see below for information.
*/
class SPU2CoreRegister_ATTR_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int DMABits = 0;
		static constexpr int DMAMode = 1;
		static constexpr int IRQEnable = 2;
		static constexpr int FxEnable = 3;
		static constexpr int NoiseClock = 4;
		static constexpr int Mute = 5;
		static constexpr int CoreEnable = 6;
	};

	SPU2CoreRegister_ATTR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	When this register is written to, resets the DMA transfer state.
	*/
	void writeHword(const Context_t context, const u16 value) override;

	/*
	Current auto/manual DMA transfer count state, in terms of hwords.
	Reset upon the register being written to.
	*/
	u32 mDMAOffset;
};

/*
The SPU2 Core STATX register.
It is set to 0x80 when the SPU2 DMA requires data (to write), cleared otherwise.
TODO: Check this is true for SPU2 DMA reading, it is unhandled for now.
*/
class SPU2CoreRegister_STATX_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int NeedData = 0;
	};

	SPU2CoreRegister_STATX_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The SPU2 Core ADMAS register.
Controls the Auto DMA function.
When turning ADMA off, it requires a special value to be set.
*/
class SPU2CoreRegister_ADMAS_t : public Register16_t
{
public:
	SPU2CoreRegister_ADMAS_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const int coreID);

	/*
	Returns if ADMA is enabled for this SPU2 core.
	Requires the core ID to perform this check.
	*/
	bool isADMAEnabled(const Context_t context);

	/*
	Sets the ADMAS register to a magic value when isEnded is true.
	isEnded represents if the FIFO queue is out of data, and ADMA cannot continue.
	Reverses the magic value when isEnded is false.
	TODO: Confirm special values are actually needed, it is in SPU2-X, but not checked against BIOS code.
	*/
	void setADMAEnd(const Context_t context, const bool isEnded);

private:
	/*
	The associated core ID.
	*/
	int mCoreID;
};
