#ifndef MWINDOWWIN32OPTIONS_HPP
#define MWINDOWWIN32OPTIONS_HPP

#include <Windows.h>
#include "MWindowWin32.hpp"

namespace MWindowWin32Options {
	static LRESULT CALLBACK onMessage(HWND hWnd, UINT mess, WPARAM wp, LPARAM lp) {
		MWindowWin32* window = 
			reinterpret_cast<MWindowWin32*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
		
		if (window)
			window->handleEvent(mess, wp, lp);

		if (mess == WM_CLOSE)
			return 0;

		return DefWindowProcW(hWnd, mess, wp, lp);
	}

	static constexpr wchar_t ClassName[] = L"MWINDOWCLASS";
	static constexpr wchar_t Title[] = L"Demo";
	
	static const WNDCLASSW& getClass() {
		static WNDCLASSW cls{
			CS_HREDRAW | CS_VREDRAW,
			onMessage,
			NULL, NULL,
			nullptr,
			nullptr,
			LoadCursorW(nullptr, IDC_ARROW),
			nullptr,
			nullptr,
			ClassName
		};
		return cls;
	}

	enum Attrib {
		ExStyle = WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW,
		Style = WS_OVERLAPPEDWINDOW,
		X = CW_USEDEFAULT,
		Y = CW_USEDEFAULT,
		Width = CW_USEDEFAULT,
		Height = CW_USEDEFAULT
	};
}

#endif //!MWINDOWWIN32OPTIONS_HPP