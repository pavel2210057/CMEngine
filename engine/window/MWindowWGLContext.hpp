#ifndef MWINDOWWGLCONTEXT_HPP
#define MWINDOWWGLCONTEXT_HPP

#include "../base/MBaseObject.hpp"
#include <glew.h>
#include <wglew.h>

class MWindowWGLContext :
	public MBaseObject {
	HGLRC hGLRC;
public:
	MWindowWGLContext(const HDC& hDC);

	virtual ~MWindowWGLContext() noexcept = default;

	operator const HGLRC& () const noexcept;

	virtual const char* toString() const noexcept { return "WindowWGLContext"; }
};

#endif //!MWINDOWWGLCONTEXT_HPP