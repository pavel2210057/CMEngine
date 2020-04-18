#ifndef MWINDOWEVENT_HPP
#define MWINDOWEVENT_HPP

#include "../base/MBaseEvent.hpp"

enum class MKey {
	A = 65,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	a = 97,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,
	LShift = 160,
	RShift,
	LCtrl,
	RCtrl,
	None = 0
};

enum class MMouseButton {
	Left = 1,
	Right,
	Middle = 16
};

enum class MWindowEventsList {
	None,
	Show,
	Hide,
	Create,
	Paint,
	Resize,
	Move,
	Close,
	KeyDown,
	KeyUp,
	MouseMove,
	MouseDown,
	MouseUp,
	MouseDblClk
};

struct MWindowEventInfo {
	MWindowEventsList m_event;
	MKey m_key;
	MMouseButton m_mouse;
	bool m_shift;
	bool m_ctrl;
};

struct MWindowEvent :
	public MBaseEvent<MWindowEventInfo> {
	MWindowEvent() noexcept {}

	virtual ~MWindowEvent() noexcept = default;
};

#endif //!MWINDOWEVENT_HPP