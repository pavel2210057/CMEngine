#ifndef MWGLCHECKER_HPP
#define MWGLCHECKER_HPP

#include <glew.h>

class MWGLChecker {
public:
	static bool hasError(unsigned int code) noexcept { return code != GLEW_OK; }

	static void traceError(unsigned int code) {
		if (hasError(code))
			throw code;
	}
};

#endif //!MWGLCHECKER_HPP