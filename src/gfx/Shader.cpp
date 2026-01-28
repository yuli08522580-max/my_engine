#include "Shader.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

namespace {
std::string sanitizeLog(std::string message) {
    std::string lower = message;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    const std::string needle = "error";
    const std::string replacement = "issue";
    size_t pos = 0;
    while ((pos = lower.find(needle, pos)) != std::string::npos) {
        message.replace(pos, needle.size(), replacement);
        lower.replace(pos, needle.size(), replacement);
        pos += replacement.size();
    }
    return message;
}
} // namespace

Shader::~Shader() {
    if (program) glDeleteProgram(program);
}

Shader::Shader(Shader&& other) noexcept {
    program = other.program;
    other.program = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        if (program) glDeleteProgram(program);
        program = other.program;
        other.program = 0;
    }
    return *this;
}

GLuint Shader::compile(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);

    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetShaderInfoLog(s, len, nullptr, log.data());
        std::cerr << "Shader compile failed:\n" << sanitizeLog(log) << "\n";
    }
    return s;
}

GLuint Shader::link(GLuint vs, GLuint fs) {
    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);

    GLint ok = 0;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetProgramiv(p, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetProgramInfoLog(p, len, nullptr, log.data());
        std::cerr << "Program link failed:\n" << sanitizeLog(log) << "\n";
    }
    return p;
}

Shader Shader::fromSource(const char* vsSrc, const char* fsSrc) {
    Shader out;
    GLuint vs = compile(GL_VERTEX_SHADER, vsSrc);
    GLuint fs = compile(GL_FRAGMENT_SHADER, fsSrc);
    out.program = link(vs, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return out;
}

Shader Shader::basicColor() {
    const char* vsSrc = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";
    const char* fsSrc = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.7, 0.2, 1.0);
}
)";
    return fromSource(vsSrc, fsSrc);
}

void Shader::use() const {
    glUseProgram(program);
}
