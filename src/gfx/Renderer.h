// gfx/Renderer.h
#pragma once

class Mesh;
class Shader;

class Renderer {
public:
    void clear(float r, float g, float b, float a);
    void draw(const Mesh& mesh, const Shader& shader);
};
