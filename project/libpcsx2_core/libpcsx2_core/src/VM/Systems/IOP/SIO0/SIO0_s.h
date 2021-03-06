#pragma once

#include "VM/Types/VMSystem_t.h"

class SIO0_t;
class IOPIntc_t;

/*
SIO0 system logic.
TODO: Fill in.
*/
class SIO0_s : public VMSystem_t
{
public:
	SIO0_s(VM * vm);
	virtual ~SIO0_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Steps through the SIO0 state, performing the following tasks:
	*/
	int step(const Event_t & event) override;

	/*
	Context resources needed.
	*/
	std::shared_ptr<SIO0_t> mSIO0;
	std::shared_ptr<IOPIntc_t> mINTC;

};

