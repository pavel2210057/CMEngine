#ifndef MVERTEXBUFFER_HPP
#define MVERTEXBUFFER_HPP

#include "../base/MBaseObject.hpp"
#include <glew.h>

enum class MUsageType {
	Static = GL_STATIC_DRAW,
	Dynamic = GL_DYNAMIC_DRAW,
	Stream = GL_STREAM_DRAW
};

class MVertexBuffer :
	public MBaseObject {
	GLuint m_buffer;
public:
	MVertexBuffer() noexcept;

	~MVertexBuffer() noexcept;

	void bind() const noexcept;

	template <MUsageType type, typename T>
	void fill(const T* data, size_t length) const noexcept {
		bind();
		glBufferData(
			GL_ARRAY_BUFFER,
			length * sizeof(T),
			reinterpret_cast<const void*>(data),
			static_cast<GLenum>(type)
		);
		unbind();
	}

	template <typename T>
	void update(size_t offset, const T* data, size_t length) const noexcept {
		bind();
		glBufferSubData(
			GL_ARRAY_BUFFER,
			offset,
			length * sizeof(T),
			reinterpret_cast<const void*>(data)
		);
		unbind();
	}

	virtual const char* toString() const noexcept { return "VertexBuffer"; }

	static void unbind() noexcept;
};

#endif //!MVERTEXBUFFER_HPP