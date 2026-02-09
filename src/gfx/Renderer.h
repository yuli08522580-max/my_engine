// gfx/Renderer.h
#pragma once

class Mesh;
class Shader;

// 描画ターゲットのクリアとメッシュ描画を担当するレンダラー。
class Renderer {
public:
    // 画面を指定色でクリアする。
    void clear(float r, float g, float b, float a);
    // 指定シェーダーを使ってメッシュを描画する。
    void draw(const Mesh& mesh, const Shader& shader);
};
