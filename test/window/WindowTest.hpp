#ifndef WINDOWTEST_HPP
#define WINDOWTEST_HPP

#include <engine/window/MWindowWin32.hpp>

void test() {
	MWindowWin32* window = MWindowWin32::getInstanse();

	window->show();
	
	while (window->isOpen())
		window->peekMessage();
}

#endif //!WINDOWTEST_HPP