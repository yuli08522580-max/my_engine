#pragma once
#include <glad/glad.h>

class Shader {
public:
    Shader() = default;
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    static Shader fromSource(const char* vsSrc, const char* fsSrc);
    static Shader basicColor(); // いまの三角用
    static Shader vertexColor();

    void use() const;
    GLuint id() const { return program; }

private:
    static GLuint compile(GLenum type, const char* src);
    static GLuint link(GLuint vs, GLuint fs);

private:
    GLuint program = 0;
};
