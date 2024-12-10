#include "FrameBuffer.h"
#include "Render.h"

#include <iostream>

FrameBuffer::FrameBuffer() {
	GLCall(glGenFramebuffers(1, &m_RenderID));
}

FrameBuffer::~FrameBuffer() {
	GLCall(glDeleteBuffers(1, &m_RenderID));
}

void FrameBuffer::Bind() const {
	GLCall(GL_FRAMEBUFFER, m_RenderID);
}

void FrameBuffer::UnBind() const {
	
}

bool FrameBuffer::BufferComplete() {
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		return false;
	}
	return true;
}


