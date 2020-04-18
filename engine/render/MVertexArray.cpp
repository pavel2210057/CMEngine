#include "MVertexArray.hpp"

MVertexArray::MVertexArray() noexcept :
	m_array(0) {
	glGenVertexArrays(1, &this->m_array);
}

MVertexArray::~MVertexArray() noexcept {
	glDeleteVertexArrays(1, &this->m_array);
}

void MVertexArray::bind() const noexcept {
	glBindVertexArray(this->m_array);
}

void MVertexArray::unbind() noexcept {
	glBindVertexArray(0);
}