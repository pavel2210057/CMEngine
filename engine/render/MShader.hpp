#ifndef MSHADER_HPP
#define MSHADER_HPP

#include "../base/MBaseObject.hpp"
#include "MVertexBuffer.hpp"
#include "MVertexArray.hpp"
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <list>

struct MShaderParam;

enum class MGLType {
	Byte = GL_BYTE,
	UByte,
	Short,
	UShort,
	Int,
	UInt,
	Float,
	Double = GL_DOUBLE
};

template <typename T, MGLType type, GLint size>
struct MAttribParam;

template <typename T>
struct MUniformParam;

class MShader :
	public MBaseObject {
	GLuint m_program;
public:
	MShader(const char* vsrc, const char* fsrc);

	virtual ~MShader() noexcept;

	void apply() const noexcept;

	GLuint getProgram() const noexcept { return this->m_program; }

	virtual const char* toString() const noexcept { return "Shader"; }
};

struct MShaderParam abstract {
	GLint m_location;

	MShaderParam(GLint location) noexcept :
		m_location(location) {}

	~MShaderParam() noexcept = default;

	virtual void use() const noexcept = 0;
};

template <typename T, MGLType type, GLint size>
struct MAttribParam : public MShaderParam {
	using MyValueType = T;
	std::vector<MyValueType> m_data;
	GLboolean m_normalized;
	GLsizei m_stride;
	MVertexBuffer m_buffer;

	MAttribParam(GLint location) noexcept :
		MShaderParam(location),
		m_normalized(false),
		m_stride(0) {}

	~MAttribParam() noexcept = default;

	template <MUsageType type>
	void fillBuffer() const noexcept {
		this->m_buffer.fill<type>(
			&this->m_data[0],
			this->m_data.size()
		);
	}

	void updateBuffer(size_t offset) const noexcept {
		this->m_buffer.update(
			offset,
			&this->m_data[0],
			this->m_data.size()
		);
	}

	void fillAttrib() const noexcept {
		this->m_buffer.bind();
		use();
		glVertexAttribPointer(
			this->m_location,
			size,
			static_cast<GLenum>(type),
			this->m_normalized,
			this->m_stride,
			reinterpret_cast<void*>(nullptr)
		);
		disable();
		this->m_buffer.unbind();
	}

	virtual void use() const noexcept {
		glEnableVertexAttribArray(this->m_location);
	}

	void disable() const noexcept {
		glDisableVertexAttribArray(this->m_location);
	}
};

template <typename T>
struct MUniformParam abstract { using MyValueType = T; };

template<>
struct MUniformParam<glm::ivec1> : public MShaderParam {
	using MyValueType = glm::ivec1;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<int>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform1iv(this->m_location, 1, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::ivec2> : public MShaderParam {
	using MyValueType = glm::ivec2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform2iv(this->m_location, 2, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::ivec3> : public MShaderParam {
	using MyValueType = glm::ivec3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform3iv(this->m_location, 3, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::ivec4> : public MShaderParam {
	using MyValueType = glm::ivec4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform4iv(this->m_location, 4, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::bvec1> : public MUniformParam<glm::ivec1> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::ivec1>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::bvec2> : public MUniformParam<glm::ivec2> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::ivec2>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::bvec3> : public MUniformParam<glm::ivec3> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::ivec3>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::bvec4> : public MUniformParam<glm::ivec4> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::ivec4>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template<>
struct MUniformParam<glm::uvec1> : public MShaderParam {
	using MyValueType = glm::uvec1;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform1uiv(this->m_location, 1, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::uvec2> : public MShaderParam {
	using MyValueType = glm::uvec2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform2uiv(this->m_location, 2, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::uvec3> : public MShaderParam {
	using MyValueType = glm::uvec3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform3uiv(this->m_location, 3, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::uvec4> : public MShaderParam {
	using MyValueType = glm::uvec4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform4uiv(this->m_location, 4, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::fvec1> : public MShaderParam {
	using MyValueType = glm::fvec1;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform1fv(this->m_location, 1, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::fvec2> : public MShaderParam {
	using MyValueType = glm::fvec2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform2fv(this->m_location, 2, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::fvec3> : public MShaderParam {
	using MyValueType = glm::fvec3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform3fv(this->m_location, 3, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::fvec4> : public MShaderParam {
	using MyValueType = glm::fvec4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform4fv(this->m_location, 4, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::dvec1> : public MShaderParam {
	using MyValueType = glm::dvec1;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform1dv(this->m_location, 1, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::dvec2> : public MShaderParam {
	using MyValueType = glm::dvec2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform2dv(this->m_location, 2, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::dvec3> : public MShaderParam {
	using MyValueType = glm::dvec3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform3dv(this->m_location, 3, glm::value_ptr(this->m_data));
	}
};

template<>
struct MUniformParam<glm::dvec4> : public MShaderParam {
	using MyValueType = glm::dvec4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniform4dv(this->m_location, 4, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::fmat2x2> : public MShaderParam {
	using MyValueType = glm::fmat2x2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix2fv(this->m_location, 4, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::fmat2x3> : public MShaderParam {
	using MyValueType = glm::fmat2x3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix2x3fv(this->m_location, 6, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::fmat2x4> : public MShaderParam {
	using MyValueType = glm::fmat2x4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix2x4fv(this->m_location, 4, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::fmat3x2> : public MShaderParam {
	using MyValueType = glm::fmat3x2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix3x2fv(this->m_location, 6, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::fmat3x3> : public MShaderParam {
	using MyValueType = glm::fmat3x3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix3fv(this->m_location, 9, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::fmat3x4> : public MShaderParam {
	using MyValueType = glm::fmat3x4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix3x4fv(this->m_location, 12, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::fmat4x2> : public MShaderParam {
	using MyValueType = glm::fmat4x2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix4x2fv(this->m_location, 8, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::fmat4x3> : public MShaderParam {
	using MyValueType = glm::fmat4x3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix4x3fv(this->m_location, 12, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::fmat4x4> : public MShaderParam {
	using MyValueType = glm::fmat4x4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix4fv(this->m_location, 16, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::imat2x2> : public MUniformParam<glm::fmat2x2> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat2x2>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::imat2x4> : public MUniformParam<glm::fmat2x4> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat2x4>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::imat3x2> : public MUniformParam<glm::fmat3x2> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat3x2>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::imat3x3> : public MUniformParam<glm::fmat3x3> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat3x3>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::imat3x4> : public MUniformParam<glm::fmat3x4> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat3x4>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::imat4x2> : public MUniformParam<glm::fmat4x2> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat4x2>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::imat4x3> : public MUniformParam<glm::fmat4x3> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat4x3>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::imat4x4> : public MUniformParam<glm::fmat4x4> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat4x4>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::umat2x2> : public MUniformParam<glm::fmat2x2> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat2x2>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::umat2x4> : public MUniformParam<glm::fmat2x4> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat2x4>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::umat3x2> : public MUniformParam<glm::fmat3x2> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat3x2>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::umat3x3> : public MUniformParam<glm::fmat3x3> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat3x3>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::umat3x4> : public MUniformParam<glm::fmat3x4> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat3x4>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::umat4x2> : public MUniformParam<glm::fmat4x2> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat4x2>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::umat4x3> : public MUniformParam<glm::fmat4x3> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat4x3>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::umat4x4> : public MUniformParam<glm::fmat4x4> {
	MUniformParam(GLint location) noexcept :
		MUniformParam<glm::fmat4x4>(location) {}

	virtual ~MUniformParam() noexcept = default;
};

template <>
struct MUniformParam<glm::dmat2x2> : public MShaderParam {
	using MyValueType = glm::dmat2x2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix2dv(this->m_location, 4, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::dmat2x3> : public MShaderParam {
	using MyValueType = glm::dmat2x3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix2x3dv(this->m_location, 6, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::dmat2x4> : public MShaderParam {
	using MyValueType = glm::dmat2x4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix2x4dv(this->m_location, 4, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::dmat3x2> : public MShaderParam {
	using MyValueType = glm::dmat3x2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix3x2dv(this->m_location, 6, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::dmat3x3> : public MShaderParam {
	using MyValueType = glm::dmat3x3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix3dv(this->m_location, 9, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::dmat3x4> : public MShaderParam {
	using MyValueType = glm::dmat3x4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix3x4dv(this->m_location, 12, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::dmat4x2> : public MShaderParam {
	using MyValueType = glm::dmat4x2;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix4x2dv(this->m_location, 8, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::dmat4x3> : public MShaderParam {
	using MyValueType = glm::dmat4x3;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix4x3dv(this->m_location, 12, false, glm::value_ptr(this->m_data));
	}
};

template <>
struct MUniformParam<glm::dmat4x4> : public MShaderParam {
	using MyValueType = glm::dmat4x4;
	MyValueType m_data;

	MUniformParam(GLint location) noexcept :
		MShaderParam(location),
		m_data(static_cast<typename MyValueType::value_type>(0)) {}

	virtual ~MUniformParam() noexcept = default;

	virtual void use() const noexcept {
		glUniformMatrix4dv(this->m_location, 16, false, glm::value_ptr(this->m_data));
	}
};

#endif //!MSHADER_HPP