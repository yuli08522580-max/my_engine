#pragma once
#include <glad/glad.h>

// 描画用メッシュ（VAO/VBO）の所有と生成を扱うユーティリティ。
class Mesh {
public:
    // 空のメッシュを生成する。
    Mesh() = default;
    // 保持しているGPUリソースを解放する。
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    // GPUハンドルの所有権をムーブする。
    Mesh(Mesh&& other) noexcept;
    // GPUハンドルの所有権をムーブ代入する。
    Mesh& operator=(Mesh&& other) noexcept;

    // 2D三角形メッシュを生成して返す。
    static Mesh triangle2D();
    // このメッシュを現在のコンテキストに描画する。
    static Mesh marioSprite();
    static Mesh marioSprite(int frame);
    // 白いドット描画に使う単色四角メッシュ。
    static Mesh dotSprite(float size = 0.05f);
    // 任意色の四角メッシュを生成する。
    static Mesh coloredQuad(float size, float r, float g, float b);
    // 現在のメッシュを描画する。
    void draw() const;

private:
    // 頂点配列オブジェクト。
    GLuint vao = 0;
    // 頂点バッファオブジェクト。
    GLuint vbo = 0;
    // 描画する頂点数。
    GLsizei count = 0;
};

