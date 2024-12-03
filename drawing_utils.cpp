//
// Created by devkon on 12/2/24.
//

#include "drawing_utils.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <vector>
#include <iostream>

// Generate grid vertices
void GenerateGrid(std::vector<float>& gridVertices, float size, float spacing) {
    float halfSize = size / 2.0f;
    for (float i = -halfSize; i <= halfSize; i += spacing) {
        // Gradient colors
        float colorValue = (i + halfSize) / (2.0f * halfSize); // Normalize to 0-1

        // Lines parallel to the X-axis
        gridVertices.insert(gridVertices.end(), {
            -halfSize, 0.0f, static_cast<float>(i), colorValue, 0.5f, 1.0f, // Start point
             halfSize, 0.0f, static_cast<float>(i), colorValue, 0.5f, 1.0f  // End point
        });

        // Lines parallel to the Z-axis
        gridVertices.insert(gridVertices.end(), {
            static_cast<float>(i), 0.0f, -halfSize, 1.0f, colorValue, 0.5f, // Start point
            static_cast<float>(i), 0.0f,  halfSize, 1.0f, colorValue, 0.5f  // End point
        });
    }
}

// Create grid data
GridData CreateGrid() {
    GridData gridData;

    // Generate the grid vertices
    GenerateGrid(gridData.vertices);

    // Generate and bind VAO and VBO
    glGenVertexArrays(1, &gridData.vao);
    glGenBuffers(1, &gridData.vbo);

    glBindVertexArray(gridData.vao);
    glBindBuffer(GL_ARRAY_BUFFER, gridData.vbo);
    glBufferData(GL_ARRAY_BUFFER, gridData.vertices.size() * sizeof(float), gridData.vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Shader program
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 color;

        out vec3 fragColor;

        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            fragColor = color;
            gl_Position = projection * view * vec4(position, 1.0);
        }
    )";


    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 fragColor;
        out vec4 FragColor;

        void main() {
            FragColor = vec4(fragColor, 1.0);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    gridData.shaderProgram = glCreateProgram();
    glAttachShader(gridData.shaderProgram, vertexShader);
    glAttachShader(gridData.shaderProgram, fragmentShader);
    glLinkProgram(gridData.shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return gridData;
}

// Draw the grid
void DrawGrid(const GridData& grid, const glm::mat4& view, const glm::mat4& projection) {
    glUseProgram(grid.shaderProgram);

    glUniformMatrix4fv(glGetUniformLocation(grid.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(grid.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(grid.vao);
    glDrawArrays(GL_LINES, 0, grid.vertices.size() / 6);
    glBindVertexArray(0);

    glUseProgram(0);
}

