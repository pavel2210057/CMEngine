#ifndef MBASESINGLETON_HPP
#define MBASESINGLETON_HPP

#include "MBaseObject.hpp"

template <typename T>
class MBaseSingleton :
	public MBaseObject {
public:
	static T* const getInstanse() noexcept {
		static T instance;
		return &instance;
	}

	virtual ~MBaseSingleton() noexcept = default;
protected:
	MBaseSingleton() noexcept = default;

	MBaseSingleton(const MBaseSingleton&) noexcept = default;

	MBaseSingleton(MBaseSingleton&&) noexcept = default;
};

#endif //!MBASESINGLETON_HPP