#include "Mesh.h"
#include <array>
#include <string>
#include <unordered_map>
#include <vector>

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

Mesh Mesh::marioSprite() {
    return marioSprite(0);
}

Mesh Mesh::marioSprite(int frame) {
    Mesh m;
    const std::array<std::array<std::string, 16>, 2> patterns = {{
        {
            "....RRRRRRRR....",
            "....RRRRRRRR....",
            "...RRRRRRRRRR...",
            "...RRSSSSSSRR...",
            "..RRSSSSSSSSRR..",
            "..RRSSSSSSSSRR..",
            "..RRYYSSSSYYRR..",
            "...RYYYYYYYYR...",
            "...RBBBBBBBBR...",
            "..RRBBBBBBBBRR..",
            ".RRRBBBBBBBBRRR.",
            ".RRRBBBBBBBBRRR.",
            "..RRBBBBBBBBRR..",
            "..RRBB....BBRR..",
            "..RRR....RRR....",
            "....YY....YY....",
        },
        {
            "....RRRRRRRR....",
            "....RRRRRRRR....",
            "...RRRRRRRRRR...",
            "...RRSSSSSSRR...",
            "..RRSSSSSSSSRR..",
            "..RRSSSSSSSSRR..",
            "..RRYYSSSSYYRR..",
            "...RYYYYYYYYR...",
            "...RBBBBBBBBR...",
            "..RRBBBBBBBBRR..",
            ".RRRBBBBBBBBRRR.",
            ".RRRBBBBBBBBRRR.",
            "..RRBBBBBBBBRR..",
            "..RR..BB..BBRR..",
            "..RRR..RR..RR...",
            "....YY....YY....",
        },
    }};

    const int frameIndex = frame % static_cast<int>(patterns.size());
    const auto& pattern = patterns[frameIndex];

    struct Color {
        float r;
        float g;
        float b;
    };

    const std::unordered_map<char, Color> palette = {
        {'R', {0.82f, 0.12f, 0.12f}},
        {'S', {1.00f, 0.80f, 0.60f}},
        {'B', {0.10f, 0.20f, 0.80f}},
        {'Y', {0.45f, 0.24f, 0.08f}},
    };

    const int rows = static_cast<int>(pattern.size());
    const int cols = static_cast<int>(pattern[0].size());
    const float size = 1.2f;
    const float pixel = size / static_cast<float>(cols);
    const float startX = -size * 0.5f;
    const float startY = size * 0.5f;

    std::vector<float> verts;
    verts.reserve(rows * cols * 6 * 5);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            char c = pattern[row][col];
            if (c == '.') {
                continue;
            }
            auto it = palette.find(c);
            if (it == palette.end()) {
                continue;
            }
            const Color color = it->second;

            float x0 = startX + static_cast<float>(col) * pixel;
            float x1 = x0 + pixel;
            float y0 = startY - static_cast<float>(row) * pixel;
            float y1 = y0 - pixel;

            float quad[] = {
                x0, y0, color.r, color.g, color.b,
                x1, y0, color.r, color.g, color.b,
                x1, y1, color.r, color.g, color.b,
                x0, y0, color.r, color.g, color.b,
                x1, y1, color.r, color.g, color.b,
                x0, y1, color.r, color.g, color.b,
            };
            verts.insert(verts.end(), std::begin(quad), std::end(quad));
        }
    }

    m.count = static_cast<GLsizei>(verts.size() / 5);

    glGenVertexArrays(1, &m.vao);
    glGenBuffers(1, &m.vbo);

    glBindVertexArray(m.vao);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return m;
}

void Mesh::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glBindVertexArray(0);
}
