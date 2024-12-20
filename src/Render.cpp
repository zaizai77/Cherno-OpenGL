#include "Render.h"

#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR) {

    }
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ")" << function << " "
            << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

void Render::Clear() const {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
}

void Render::DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    //Draw call
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Render::DrawArrays(const VertexArray& va, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, va.GetCount()));
}