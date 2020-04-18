#ifndef MACTIVESHADER_HPP
#define MACTIVESHADER_HPP

#include "../base/MBaseSingleton.hpp"
#include "MShader.hpp"

class MActiveShader :
	public MBaseSingleton<MActiveShader> {
	
private:
	friend class MBaseSingleton<MActiveShader>;
};

#endif //!MACTIVESHADER_HPP