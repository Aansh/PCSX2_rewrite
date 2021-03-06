#pragma once

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Types/VMSystem_t.h"

class CRTC_t;
class Events_t;
class EEIntc_t;
class IOPIntc_t;

/*
PCRTC system logic.
http://psx-scene.com/forums/f291/gs-mode-selector-development-feedback-61808/
https://en.wikipedia.org/wiki/Phase-locked_loop
SCPH-39001 service manual.

TODO: I have no idea how this works, it is based of guessed logic and pixel clock speed from resX and fH. Read through the GS mode selector docs above / general info on CRTC's.
*/
class CRTC_s : public VMSystem_t
{
public:
	CRTC_s(VM * vm);
	virtual ~CRTC_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Steps through the CRTC, incrementing the number of pixels based on the CRTC configuration.
	When a row of pixels has been completed (scanline), copy's the row to the VM buffer and sends a HBlank clock event to EE/IOP Timers.
	When a whole frame/field has been completed, calls the VM render function and sends a VBlank start/end interrupt to the EE/IOP Intc.
	*/
	int step(const Event_t & event) override;

	/*
	Resources.
	*/
	std::shared_ptr<CRTC_t> mCRTC;
	std::shared_ptr<Events_t> mEvents;
	std::shared_ptr<EEIntc_t> mEEINTC;
	std::shared_ptr<IOPIntc_t> mIOPINTC;
};