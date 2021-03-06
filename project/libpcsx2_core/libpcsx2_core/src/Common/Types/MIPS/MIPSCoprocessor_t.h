#pragma once

#include "Common/Types/System/Context_t.h"

/*
Represents a MIPS co-processor base class.
Functions listed here are common to all co-processors.
*/
class MIPSCoprocessor_t
{
public:
	virtual ~MIPSCoprocessor_t() = default;

	/*
	Checks if this coprocessor is usable. As the coprocessor can be used within different CPU's, it is left as virtual.
	*/
	virtual bool isCoprocessorUsable(const Context_t context) const = 0;

	/*
	An initialisation function for the coprocessor state.
	*/
	virtual void initialise() { }
};