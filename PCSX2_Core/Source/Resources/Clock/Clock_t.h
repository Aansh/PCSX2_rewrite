#pragma once

#include <map>

#include "Common/Types/System_t.h"
#include "Common/Types/ClockSource_t.h"
#include "Common/Types/EnumMap_t.h"
#include <mutex>

/*
Clock_t helps with synchronisation across components.
*/
class Clock_t
{
public:
	Clock_t();

	/*
	Sets the system biases, used when adding ticks to a source.
	When ticks are added to a system, the ticks are multiplied by the bias (regardless of which clock source it is for).
	*/
	void setSystemClockBiases(const std::map<System_t, double> & biases);

	/*
	Returns an immutable reference to the system clock state.
	Becuase it is used in a multiple producers, single consumer scenario, no locking is required for reading it.
	It does not matter if the callee reads an older state (and then writes this), it will just have delayed execution the next time.
	Use the add/sub tick functions to modify the state.
	*/
	const EnumMap_t<ClockSource_t, double> & getSystemClockTicks(const System_t system);

	/*
	Adds ticks to all of the "independent" sources in the PS2, such as the EECoreClock, EEBusClock, etc that run at a fixed rate.
	(Counter-example is HblankClock, which is "dependant" and generated by the PCRTC on every completed scanline.)
	This is used to give the systems execution time that is consumed when they are run.
	The clock states are locked.
	*/
	void addSystemClockTicksAll(const double time);

	/*
	Adds ticks to the given system's clock source.
	The system bias is applied (multiplied) when adding the ticks.
	*/
	void addSystemClockTicks(const System_t system, const ClockSource_t clockSource, const int ticks);

	/*
	Subtracts ticks from the given system's clock source.
	The system bias is NOT applied to this!
	*/
	void subSystemClockTicks(const System_t system, const ClockSource_t clockSource, const int ticks);

	/*
	Calculates and sets the pixel clock speed used by addSystemClockTicksAll().
	resX represents the visible horizontal resolution in pixels.
	fH represents the horizontal (scanline) refresh frequency in Hz.
	*/
	void setPixelClockSpeed(const int resX, const double fH);

private:
	/*
	System clock/tick state map.
	*/
	struct SystemClockData_t
	{
		double bias;
		EnumMap_t<ClockSource_t, double> state;
	};
	EnumMap_t<System_t, SystemClockData_t> mSystemTickState;
	std::mutex mSystemTickWriteMutex;

	/*
	Pixel clock current speed.
	*/
	double mPixelClockSpeed;

	// DEBUG: time elapsed counter (us).
	double DEBUG_TIME_ELAPSED_CURRENT;
	double DEBUG_TIME_ELAPSED_LAST;
};

