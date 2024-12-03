//
// Created by devkon on 12/3/24.
//

#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

unsigned int CreateShaderProgram(const char* vertexPath, const char* fragmentPath);
unsigned int CompileShader(unsigned int type, const std::string& source);
std::string ReadShaderFile(const char* filePath);

#endif //SHADER_H
