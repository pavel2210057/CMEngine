#ifndef MWINDOWWGLCONTEXTOPTIONS_HPP
#define MWINDOWWGLCONTEXTOPTIONS_HPP

#include <glew.h>
#include <wglew.h>

namespace MWindowWGLContextOptions {
	static constexpr PIXELFORMATDESCRIPTOR pixelFormatHandle = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		8, 16,
		8, 8,
		8, 0,
		0, 0,
		64,
		16,
		16,
		16, 
		0,
		32,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0,
		0,
		0
	};

	static constexpr int attribs[] = {
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		NULL
	};
}

#endif //!MWINDOWWGLCONTEXTOPTIONS_HPP