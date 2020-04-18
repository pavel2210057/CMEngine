#include "MWindowWin32.hpp"
#include "MWindowWin32Options.hpp"

MWindowWin32::MWindowWin32() noexcept {
	auto a = RegisterClassW(&MWindowWin32Options::getClass());

	this->m_hWnd = CreateWindowExW(
		MWindowWin32Options::Attrib::ExStyle,
		MWindowWin32Options::ClassName,
		MWindowWin32Options::Title,
		MWindowWin32Options::Attrib::Style,
		MWindowWin32Options::Attrib::X,
		MWindowWin32Options::Attrib::Y,
		MWindowWin32Options::Attrib::Width,
		MWindowWin32Options::Attrib::Height,
		nullptr,
		nullptr,
		nullptr,
		NULL
	);

	SetWindowLongPtrW(
		this->m_hWnd,
		GWLP_USERDATA,
		reinterpret_cast<LONG_PTR>(this)
	);

	this->m_hDC = GetDC(this->m_hWnd);
	this->m_isFullscreen = false;
	this->m_isShownCursor = true;
}

void MWindowWin32::peekMessage() noexcept {
	static MSG msg;
	while (PeekMessageW(&msg, this->m_hWnd, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void MWindowWin32::show() noexcept { 
	ShowWindow(this->m_hWnd, SW_NORMAL);
	pushEvent<MWindowEventsList::Show>();
}

void MWindowWin32::hide() noexcept {
	ShowWindow(this->m_hWnd, SW_MINIMIZE);
	pushEvent<MWindowEventsList::Hide>();
}

void MWindowWin32::fullscreen(bool isFullscreen) noexcept {
	if (this->m_isFullscreen == isFullscreen)
		return;

	if (isFullscreen)
		toFullscreen();
	else
		toNormal();

	this->m_isFullscreen = isFullscreen;
}

void MWindowWin32::showCursor(bool isShow) noexcept {
	if (this->m_isShownCursor == isShow)
		return;

	ShowCursor(isShow);
	this->m_isShownCursor = isShow;
}

void MWindowWin32::close() noexcept {
	CloseWindow(this->m_hWnd);
	this->m_hWnd = nullptr;
	pushEvent<MWindowEventsList::Close>();
}

void MWindowWin32::handleEvent(UINT message, WPARAM wp, LPARAM lp) noexcept {
	switch (message) {
	case WM_KEYDOWN:
		this->m_event.info.m_key = static_cast<MKey>(wp);
		pushEvent<MWindowEventsList::KeyDown>();
		break;
	case WM_KEYUP:
		this->m_event.info.m_key = static_cast<MKey>(wp);
		pushEvent<MWindowEventsList::KeyUp>();
		break;
	case WM_MOUSEMOVE:
		pushEvent<MWindowEventsList::MouseMove>();
		break;
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
		this->m_event.info.m_mouse = static_cast<MMouseButton>(wp);
		pushEvent<MWindowEventsList::MouseDown>();
		break;
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		this->m_event.info.m_mouse = static_cast<MMouseButton>(wp);
		pushEvent<MWindowEventsList::MouseUp>();
		break;
	case WM_RBUTTONDBLCLK:
	case WM_LBUTTONDBLCLK:
		this->m_event.info.m_mouse = static_cast<MMouseButton>(wp);
		pushEvent<MWindowEventsList::MouseDblClk>();
		break;
	case WM_PAINT:
		pushEvent<MWindowEventsList::Paint>();
		break;
	case WM_SIZE:
		pushEvent<MWindowEventsList::Resize>();
		break;
	case WM_CLOSE:
		close();
	default:
		break;
	}
}

void MWindowWin32::swapBuffers() const noexcept {
	SwapBuffers(this->m_hDC);
}

void MWindowWin32::toFullscreen() const noexcept {
	SetWindowLongW(
		this->m_hWnd,
		GWL_EXSTYLE,
		WS_EX_TOPMOST
	);
	SetWindowLongW(
		this->m_hWnd,
		GWL_STYLE,
		WS_BORDER
	);
	ShowWindow(this->m_hWnd, SW_MAXIMIZE);
}

void MWindowWin32::toNormal() const noexcept {
	SetWindowLongW(
		this->m_hWnd,
		GWL_EXSTYLE,
		WS_EX_OVERLAPPEDWINDOW
	);
	SetWindowLongW(
		this->m_hWnd,
		GWL_STYLE,
		WS_OVERLAPPEDWINDOW
	);
	ShowWindow(this->m_hWnd, SW_NORMAL);
}