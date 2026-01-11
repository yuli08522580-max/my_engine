#include "Mesh.h"

Mesh::~Mesh() {
    if (vbo) glDeleteBuffers(1, &vbo);
    if (vao) glDeleteVertexArrays(1, &vao);
}

Mesh::Mesh(Mesh&& other) noexcept {
    vao = other.vao; other.vao = 0;
    vbo = other.vbo; other.vbo = 0;
    count = other.count; other.count = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        if (vbo) glDeleteBuffers(1, &vbo);
        if (vao) glDeleteVertexArrays(1, &vao);

        vao = other.vao; other.vao = 0;
        vbo = other.vbo; other.vbo = 0;
        count = other.count; other.count = 0;
    }
    return *this;
}

Mesh Mesh::triangle2D() {
    Mesh m;
    float verts[] = {
         0.0f,  0.6f,
        -0.6f, -0.6f,
         0.6f, -0.6f,
    };
    m.count = 3;

    glGenVertexArrays(1, &m.vao);
    glGenBuffers(1, &m.vbo);

    glBindVertexArray(m.vao);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return m;
}

void Mesh::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glBindVertexArray(0);
}
