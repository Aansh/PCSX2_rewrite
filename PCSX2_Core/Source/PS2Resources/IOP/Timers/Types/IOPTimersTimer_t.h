#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class IOPTimersTimerRegister_Mode_t;
class IOPTimersTimerRegister_Count_t;
class Register32_t;

/*
A base type representing an IOP Timers Timer.
// TODO: fill in.
*/
class IOPTimersTimer_t
{
public:
	explicit IOPTimersTimer_t(const u32 & timerID);

	/*
	The ID of this timer. Used for debug.
	*/
	const u32 mTimerID;

	/*
	IOP Timers timer registers.
	The Mode, Count and Compare registers are defined for each timer.
	Count must be initalised before Mode due to dependency.
	*/
	std::shared_ptr<IOPTimersTimerRegister_Count_t> Count;
	std::shared_ptr<IOPTimersTimerRegister_Mode_t>  Mode;
	std::shared_ptr<Register32_t>                   Compare;
};