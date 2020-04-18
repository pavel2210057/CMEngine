#ifndef MWINDOWLISTENER_HPP
#define MWINDOWLISTENER_HPP

#include "../base/MBaseListener.hpp"
#include "MWindowEvent.hpp"

class MWindowListener :
	public MBaseListener<MWindowEventsList, class MWindowWin32* const, MWindowEvent> {
public:
	MWindowListener() noexcept = default;

	virtual ~MWindowListener() noexcept = default;
	
	virtual const char* toString() const noexcept { return "WindowListener"; }
};

#endif //!MWINDOWLISTENER_HPP