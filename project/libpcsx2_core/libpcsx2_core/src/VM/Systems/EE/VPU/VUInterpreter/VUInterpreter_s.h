#pragma once

#include "Common/Global/Globals.h"

#include "VM/Types/VMSystem_t.h"

#include "Resources/EE/VPU/VU/Types/VUInstruction_t.h"

class VUCore_t;

/*
The VU0/1 interpreter.
*/
class VUInterpreter_s : public VMSystem_t
{
public:
	VUInterpreter_s(VM * vm, const int vuCoreIndex);
	virtual ~VUInterpreter_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Steps through the VU core state, executing one macro and one micro instruction.
	*/
	int step(const Event_t & event) override;

	//////////////////////////
	// Common Functionality //
	//////////////////////////

	/*
	Resources.
	*/
	std::shared_ptr<VUCore_t> mVUCore;

#if defined(BUILD_DEBUG)
	// Debug loop counter.
	u64 DEBUG_LOOP_COUNTER = 0;
#endif

	/*
	Context of which VU this system is processing.
	*/
	u32 mVUCoreIndex;

	///////////////////////////////
	// Instruction Functionality //
	///////////////////////////////

	/*
	Temporary holder for the current instruction, while the operation to perform is being determined.
	It is also used while an instruction is being performed.
	TODO: make thread safe, need to make sure if COP2 (macro) instruction is running it doesnt interfere with micro instruction running.
	*/
	VUInstruction_t mVUInstruction;

	/*
	Upper instruction functions. There are 59 instructions total.
	However, the 'bc' class instructions are split up into a base function and individual field x, y, z, w (0, 1, 2, 3) 
	 functions, in order to support the instruction table lookup, and support the EE Core (COP2) function calls.
	Only the individual field functions are called from the instruction lookup, which call the base function with the field number parameter.
	See VU Users Manual page 35.
	*/
	void ABS();
	void ADD();
	void ADDi();
	void ADDq();
	void ADDbc(const int idx);
	void ADDbc_0();
	void ADDbc_1();
	void ADDbc_2();
	void ADDbc_3();
	void ADDA();
	void ADDAi();
	void ADDAq();
	void ADDAbc(const int idx);
	void ADDAbc_0();
	void ADDAbc_1();
	void ADDAbc_2();
	void ADDAbc_3();
	void SUB();
	void SUBi();
	void SUBq();
	void SUBbc(const int idx);
	void SUBbc_0();
	void SUBbc_1();
	void SUBbc_2();
	void SUBbc_3();
	void SUBA();
	void SUBAi();
	void SUBAq();
	void SUBAbc(const int idx);
	void SUBAbc_0();
	void SUBAbc_1();
	void SUBAbc_2();
	void SUBAbc_3();
	void MUL();
	void MULi();
	void MULq();
	void MULbc(const int idx);
	void MULbc_0();
	void MULbc_1();
	void MULbc_2();
	void MULbc_3();
	void MULA();
	void MULAi();
	void MULAq();
	void MULAbc(const int idx);
	void MULAbc_0();
	void MULAbc_1();
	void MULAbc_2();
	void MULAbc_3();
	void MADD();
	void MADDi();
	void MADDq();
	void MADDbc(const int idx);
	void MADDbc_0();
	void MADDbc_1();
	void MADDbc_2();
	void MADDbc_3();
	void MADDA();
	void MADDAi();
	void MADDAq();
	void MADDAbc(const int idx);
	void MADDAbc_0();
	void MADDAbc_1();
	void MADDAbc_2();
	void MADDAbc_3();
	void MSUB();
	void MSUBi();
	void MSUBq();
	void MSUBbc(const int idx);
	void MSUBbc_0();
	void MSUBbc_1();
	void MSUBbc_2();
	void MSUBbc_3();
	void MSUBA();
	void MSUBAi();
	void MSUBAq();
	void MSUBAbc(const int idx);
	void MSUBAbc_0();
	void MSUBAbc_1();
	void MSUBAbc_2();
	void MSUBAbc_3();
	void MAX();
	void MAXi();
	void MAXbc(const int idx);
	void MAXbc_0();
	void MAXbc_1();
	void MAXbc_2();
	void MAXbc_3();
	void MINI();
	void MINIi();
	void MINIbc(const int idx);
	void MINIbc_0();
	void MINIbc_1();
	void MINIbc_2();
	void MINIbc_3();
	void OPMULA();
	void OPMSUB();
	void NOP();
	void FTOI0();
	void FTOI4();
	void FTOI12();
	void FTOI15();
	void ITOF0();
	void ITOF4();
	void ITOF12();
	void ITOF15();
	void CLIP();

	/*
	Lower instruction functions. There are 69 instructions total.
	See VU Users Manual page 37.
	*/
	void DIV();
	void SQRT();
	void RSQRT();
	void IADD();
	void IADDI();
	void IADDIU();
	void IAND();
	void IOR();
	void ISUB();
	void ISUBIU();
	void MOVE();
	void MFIR();
	void MTIR();
	void MR32();
	void LQ();
	void LQD();
	void LQI();
	void SQ();
	void SQD();
	void SQI();
	void ILW();
	void ISW();
	void ILWR();
	void ISWR();
	void LOI();
	void RINIT();
	void RGET();
	void RNEXT();
	void RXOR();
	void WAITQ();
	void FSAND();
	void FSEQ();
	void FSOR();
	void FSSET();
	void FMAND();
	void FMEQ();
	void FMOR();
	void FCAND();
	void FCEQ();
	void FCOR();
	void FCSET();
	void FCGET();
	void IBEQ();
	void IBGEZ();
	void IBGTZ();
	void IBLEZ();
	void IBLTZ();
	void IBNE();
	void B();
	void BAL();
	void JR();
	void JALR();
	void MFP();
	void WAITP();
	void ESADD();
	void ERSADD();
	void ELENG();
	void ERLENG();
	void EATANxy();
	void EATANxz();
	void ESUM();
	void ERCPR();
	void ESQRT();
	void ERSQRT();
	void ESIN();
	void EATAN();
	void EEXP();
	void XGKICK();
	void XTOP();
	void XITOP();

	/*
	Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index.
	See VUInstructionTable and "VU Instruction Implementation Register.xlsm" for more details.
	
	As mentioned above, the 'bc' class instructions are split up into the individual fields for x, y, z, w (0, 1, 2, 3) and listed instead of a generic bc-type instruction.
	*/
	void(VUInterpreter_s::* VU_INSTRUCTION_TABLE[Constants::EE::VPU::VU::NUMBER_VU_INSTRUCTIONS])() =
	{
	};
};
