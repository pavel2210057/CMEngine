#ifndef MBASEEVENT_HPP
#define MBASEEVENT_HPP

#include "MBaseObject.hpp"

template <typename Info>
struct MBaseEvent :
	public MBaseObject {
	using InfoType = Info;
	InfoType info;

	MBaseEvent() noexcept : info() {}

	virtual ~MBaseEvent() noexcept = default;

	virtual const char* toString() const noexcept { return "BaseEvent"; }
};

#endif //!MBASEEVENT_HPP