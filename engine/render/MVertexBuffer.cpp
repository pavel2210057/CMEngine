#include "MVertexBuffer.hpp"

MVertexBuffer::MVertexBuffer() noexcept :
	m_buffer(0) {
	glGenBuffers(1, &this->m_buffer);
}

MVertexBuffer::~MVertexBuffer() noexcept {
	glDeleteBuffers(1, &this->m_buffer);
}

void MVertexBuffer::bind() const noexcept {
	glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer);
}

void MVertexBuffer::unbind() noexcept {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}