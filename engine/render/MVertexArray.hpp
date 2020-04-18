#ifndef MVERTEXARRAY_HPP
#define MVERTEXARRAY_HPP

#include "../base/MBaseObject.hpp"
#include <glew.h>

class MVertexArray :
	public MBaseObject {
	GLuint m_array;
public:
	MVertexArray() noexcept;

	~MVertexArray() noexcept;

	void bind() const noexcept;

	virtual const char* toString() const noexcept { return "VertexArray"; }

	static void unbind() noexcept;
};

#endif //!MVERTEXARRAY_HPP