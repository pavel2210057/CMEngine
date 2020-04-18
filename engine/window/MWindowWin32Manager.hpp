#ifndef MWINDOWWIN32MANAGER_HPP
#define MWINDOWWIN32MANAGER_HPP

#include "../base/MBaseSingleton.hpp"
#include "MWindowWin32.hpp"
#include "MWindowWGLContext.hpp"
#include "MWindowListener.hpp"

class MWindowWin32Manager :
	public MBaseSingleton<MWindowWin32Manager> {
	MWindowWin32* const m_wnd;
	MWindowWGLContext m_context;
public:
	MWindowWin32* const getWindow() noexcept { return this->m_wnd; }

	MWindowWGLContext* const getContext() noexcept { return &this->m_context; }

	virtual const char* toString() const noexcept { return "WindowWin32Manager"; }

	virtual ~MWindowWin32Manager() noexcept = default;
protected:
	MWindowWin32Manager() :
		m_wnd(MWindowWin32::getInstanse()),
		m_context(*m_wnd) {}
private:
	friend class MBaseSingleton<MWindowWin32Manager>;
};

#endif //!MWINDOWWIN32MANAGER_HPP