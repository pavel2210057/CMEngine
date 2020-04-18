#ifndef MWINDOWWIN32_HPP
#define MWINDOWWIN32_HPP

#include <windows.h>
#include "../base/MBaseSingleton.hpp"
#include "MWindowListener.hpp"

class MWindowWin32 :
	public MBaseSingleton<MWindowWin32> {
protected:
	HWND m_hWnd;
	HDC m_hDC;
	MWindowEvent m_event;
	MWindowListener m_listener;
	bool m_isFullscreen;
	bool m_isShownCursor;
public:
	void peekMessage() noexcept;

	void show() noexcept;

	void hide() noexcept;

	void fullscreen(bool isFullscreen) noexcept;

	void showCursor(bool isShow) noexcept;

	void close() noexcept;

	void handleEvent(UINT message, WPARAM wp, LPARAM lp) noexcept;

	void swapBuffers() const noexcept;

	bool isOpen() const noexcept { return this->m_hWnd; }

	bool isFullscreen() const noexcept { return this->m_isFullscreen; }

	bool isShownCursor() const noexcept { return this->m_isShownCursor; }

	operator const HWND& () const noexcept { return this->m_hWnd; }

	operator const HDC& () const noexcept { return this->m_hDC; }

	MWindowListener* const getListener() noexcept { return &this->m_listener; }

	virtual const char* toString() const noexcept { return "WindowWin32"; }

	virtual ~MWindowWin32() noexcept { close(); }

	static bool isPressed(MKey key) noexcept {
		return GetAsyncKeyState(static_cast<int>(key));
	}
protected:
	MWindowWin32() noexcept;
private:
	template <MWindowEventsList event>
	void pushEvent() {
		this->m_event.info.m_event = event;
		this->m_listener.exec<event>(
			this,
			this->m_event
		);
	}

	void toFullscreen() const noexcept;

	void toNormal() const noexcept;

	friend class MBaseSingleton<MWindowWin32>;
};

#endif //!MWINDOWWIN32_HPP