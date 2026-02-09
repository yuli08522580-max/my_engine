#pragma once
#include <glad/glad.h>

// 描画用メッシュ（VAO/VBO）の所有と生成を扱うユーティリティ。
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
    // 白いドット描画に使う単色四角メッシュ。
    static Mesh dotSprite(float size = 0.05f);
    // 任意色の四角メッシュを生成する。
    static Mesh coloredQuad(float size, float r, float g, float b);
    // 現在のメッシュを描画する。
    void draw() const;

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLsizei count = 0;
};
