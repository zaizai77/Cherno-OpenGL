#include "Shader.h"
#include "Render.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath) 
	:m_FilePath(filepath),m_RenderID(0) {
    ShaderProgramSource source = ParseShader(filepath);
    m_RenderID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader(){
    GLCall(glDeleteProgram(m_RenderID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RenderID));
}

void Shader::UnBind() const {
    GLCall(glUseProgram(0));
}

//从文件中将着色器代码读取出来
ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //Syntax error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        //编译失败 获取错误信息
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertexShader"
            : "fragmentShader ") << " shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

//我们向OpenGL提供我们实际的着色器源代码，我的着色器文本。我们想让OpenGL编译那个程序，将这两个链接到一个
//独立的着色器程序，然后给我们一些那个着色器返回的唯一标识符，我们就可以绑定着色器并使用
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //将这两个着色器附加到我们的程序上
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    //链接程序
    glLinkProgram(program);
    glValidateProgram(program);

    //删除一些无用的中间文件
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::SetUniform1i(const std::string& name, int value) {
    int location = GetUniformLoation(name);
    GLCall(glUniform1i(location, value));
}

//Set uniforms
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3){
    int location = GetUniformLoation(name);
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    //             //name  传入多少个矩阵 是否需要转置（有行存储变为列存储），第一个元素的地址
    glUniformMatrix4fv(GetUniformLoation(name), 1, GL_FALSE, &matrix[0][0]);
}

unsigned int Shader::GetUniformLoation(const std::string& name){
    if (m_UniformLocationCache.count(name)) {
        return m_UniformLocationCache[name];
    }
    
    GLCall(int location = glGetUniformLocation(m_RenderID, name.c_str()));
    if (location == -1) {
        std::cout << "Waring: Uniform " << name <<" does not exist" << std::endl;
    }
    else {
        m_UniformLocationCache[name] = location;
    }
    return location;
}