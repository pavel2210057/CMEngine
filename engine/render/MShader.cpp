#include "MShader.hpp"

MShader::MShader(const char* vsrc, const char* fsrc) {
	GLuint vid = glCreateShader(GL_VERTEX_SHADER);
	GLint len = static_cast<GLint>(strlen(vsrc));
	glShaderSource(vid, 1, &vsrc, &len);
	glCompileShader(vid);

	char* err_buffer = new char[4096];
	glGetShaderInfoLog(vid, 4096, nullptr, err_buffer);
	if (*err_buffer) {
		glDeleteShader(vid);
		throw err_buffer;
	}

	GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);
	len = static_cast<GLuint>(strlen(fsrc));
	glShaderSource(fid, 1, &fsrc, &len);
	glCompileShader(fid);

	glGetShaderInfoLog(fid, 4096, nullptr, err_buffer);
	if (*err_buffer) {
		glDeleteShader(fid);
		throw err_buffer;
	}

	this->m_program = glCreateProgram();
	glAttachShader(this->m_program, vid);
	glAttachShader(this->m_program, fid);
	glLinkProgram(this->m_program);

	glGetProgramInfoLog(this->m_program, 4096, nullptr, err_buffer);
	if (*err_buffer) {
		glDeleteProgram(this->m_program);
		throw err_buffer;
	}

	glDeleteShader(vid);
	glDeleteShader(fid);
	delete[] err_buffer;
}

MShader::~MShader() noexcept {
	glDeleteProgram(this->m_program);
}

void MShader::apply() const noexcept {
	glUseProgram(this->m_program);
}