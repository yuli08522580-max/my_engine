#pragma once
#include <glad/glad.h>

// OpenGLシェーダープログラムを管理するクラス。
class Shader {
public:
    // 空のシェーダーオブジェクトを生成する。
    Shader() = default;
    // 保持しているシェーダープログラムを解放する。
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // プログラムハンドルの所有権をムーブする。
    Shader(Shader&& other) noexcept;
    // プログラムハンドルの所有権をムーブ代入する。
    Shader& operator=(Shader&& other) noexcept;

    // 頂点・フラグメントシェーダー文字列からプログラムを生成する。
    static Shader fromSource(const char* vsSrc, const char* fsSrc);
        // 三角形描画用の基本色シェーダーを生成する。
    static Shader basicColor(); // いまの三角用
    static Shader vertexColor();
    static Shader vertexColorOffset();

    // このシェーダープログラムを現在の描画状態にバインドする。
    void use() const;
    // 内部のOpenGLプログラムIDを返す。
    GLuint id() const { return program; }
    void setVec2(const char* name, float x, float y) const;

private:
    // 指定タイプのシェーダーをコンパイルする。
    static GLuint compile(GLenum type, const char* src);
    // 頂点・フラグメントシェーダーをリンクしてプログラムを作成する。
    static GLuint link(GLuint vs, GLuint fs);

private:
    // OpenGLプログラムID。
    GLuint program = 0;
};