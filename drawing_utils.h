//
// Created by devkon on 12/2/24.
//

#ifndef DRAWING_UTILS_H
#define DRAWING_UTILS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

// Grid data structure
struct GridData {
    GLuint vao;
    GLuint vbo;
    GLuint shaderProgram;
    std::vector<float> vertices;
};

// Function declarations
void GenerateGrid(std::vector<float>& gridVertices, float size = 10.0f, float spacing = 1.0f);
GridData CreateGrid();
void DrawGrid(const GridData& grid, const glm::mat4& view, const glm::mat4& projection);

#endif //DRAWING_UTILS_H
