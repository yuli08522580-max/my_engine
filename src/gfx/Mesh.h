#pragma once
#include <glad/glad.h>

class Mesh {
public:
    Mesh() = default;
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    static Mesh triangle2D();
    static Mesh marioSprite();
    static Mesh marioSprite(int frame);
    static Mesh dotSprite(float size = 0.05f);
    void draw() const;

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLsizei count = 0;
};