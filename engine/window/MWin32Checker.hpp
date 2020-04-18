#ifndef MWIN32CHECKER_HPP
#define MWIN32CHECKER_HPP

#include "../base/MBaseObject.hpp"
#include <Windows.h>

class MWin32Checker {
public:
	static bool hasError() noexcept { return !::GetLastError(); }

	static DWORD getError() noexcept { return ::GetLastError(); }

	static void traceError() {
		if (int e = getError())
			throw e;
	}
};

#endif //!MWIN32CHECKER_HPP