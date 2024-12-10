#pragma once

class FrameBuffer {
private:
	unsigned int m_RenderID;
	
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind() const;
	void UnBind() const;

	bool BufferComplete();
};