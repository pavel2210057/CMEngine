#include "MWindowWGLContext.hpp"
#include "MWindowWGLContextOptions.hpp"

#ifdef _DEBUG
#include "MWGLChecker.hpp"
#endif

MWindowWGLContext::MWindowWGLContext(const HDC& hDC) {
	int format = ChoosePixelFormat(
		hDC,
		&MWindowWGLContextOptions::pixelFormatHandle
	);
	SetPixelFormat(
		hDC,
		format,
		&MWindowWGLContextOptions::pixelFormatHandle
	);

	HGLRC temp_context = wglCreateContext(hDC);
	wglMakeCurrent(hDC, temp_context);
	
	glewInit();

	this->hGLRC = wglCreateContextAttribsARB(
		hDC,
		NULL,
		MWindowWGLContextOptions::attribs
	);

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(temp_context);
	wglMakeCurrent(hDC, this->hGLRC);
}

MWindowWGLContext::operator const HGLRC& () const noexcept {
	return this->hGLRC;
}