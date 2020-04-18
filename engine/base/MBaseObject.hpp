#ifndef MBASEOBJECT_HPP
#define MBASEOBJECT_HPP

#include <iostream>
#include <string>

class MBaseObject {
protected:
	MBaseObject() noexcept = default;
public:
	virtual ~MBaseObject() noexcept = default;

	std::ostream& dump(std::ostream& os) const noexcept { return os << toString(); }

	std::ostream& clDump() const noexcept { return dump(std::cout); }

	friend std::ostream& operator<<(std::ostream& os, const MBaseObject& base) noexcept { 
		return base.dump(os);
	}

	virtual const char* toString() const noexcept { return "BaseObject"; }
};

#endif //!MBASEOBJECT_HPP