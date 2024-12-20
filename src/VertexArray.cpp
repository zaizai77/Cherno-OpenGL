#include "VertexArray.h"

#include "Render.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_RenderID));
	GLCall(glBindVertexArray(m_RenderID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_RenderID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement>& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size();i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, 
			element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	m_Count = offset;
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(m_RenderID));
}
void VertexArray::UnBind() const {
	GLCall(glBindVertexArray(0));
}