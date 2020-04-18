#ifndef SHADERTEST_HPP
#define SHADERTEST_HPP

#include <engine/window/MWindowWin32Manager.hpp>
#include <engine/render/MShader.hpp>
#include <engine/render/MVertexArray.hpp>
#include <thread>

using namespace std::chrono_literals;

void test() {
	auto window = MWindowWin32Manager::getInstanse()->getWindow();
	window->show();

	MShader shader(
		"#version 440\n"
		"layout(location=0) in vec2 aPos;"
		"layout(location=1) in vec3 aCol;"
		"out vec3 vCol;"
		"void main() {"
		"	gl_Position = vec4(aPos, 0.0, 1.0);"
		"	vCol = aCol;"
		"}",
		"#version 440\n"
		"in vec3 vCol;"
		"out vec4 oCol;"
		"void main() {"
		"	oCol = vec4(vCol, 1.0);"
		"}"
	);

	MAttribParam<float, MGLType::Float, 2> aPos(0);
	MAttribParam<float, MGLType::Float, 3> aCol(1);

	aPos.m_data.assign({
		-1.0, 1.0,
		0.0, -1.0,
		1.0, 1.0
		});
	aCol.m_data.assign({
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
		});

	MVertexArray vertexArray;
	vertexArray.bind();

	aPos.fillBuffer<MUsageType::Static>();
	aPos.fillAttrib();

	aCol.fillBuffer<MUsageType::Static>();
	aCol.fillAttrib();

	shader.apply();
	aPos.use();
	aCol.use();

	glClearColor(0.5f, 0.6f, 0.2f, 1.f);
	
	auto def_clbck = [](MWindowWin32* const win, MWindowEvent) {
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		win->swapBuffers();
	};

	window->getListener()->on<MWindowEventsList::Paint>(
		[](MWindowWin32* const win, MWindowEvent) {
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			win->swapBuffers();
		}
	);

	while (window->isOpen()) {
		window->peekMessage();
		std::this_thread::sleep_for(16ms);
	}
}

#endif //!SHADERTEST_HPP