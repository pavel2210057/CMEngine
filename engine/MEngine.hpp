#ifndef MENGINE_HPP
#define MENGINE_HPP

#include "window/MWindowWin32Manager.hpp"
#include "render/MRenderManager.hpp"

namespace MEngine {
	namespace Global {
		static MWindowWin32Manager* const windowManager = MWindowWin32Manager::getInstanse();
		static MRenderManager* const renderManager = MRenderManager::getInstanse();
	}
}

#endif //!MENGINE_HPP