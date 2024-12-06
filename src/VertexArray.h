#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
private:
	unsigned int m_RenderID;
	int m_Count;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb,const VertexBufferLayout& layout);
	inline unsigned int GetCount() const {
		return m_Count;
	}

	void Bind() const;
	void UnBind() const;
};