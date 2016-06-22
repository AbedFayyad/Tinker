//
//  shader.cpp
//  Tinker2D
//
//  Created by Abed on 2016-06-21.
//
//

#include "shader.hpp"

#include <fstream>
#include <OpenGL/gl3.h>

// TODO: error checking for missing files
std::string readFile(const char *filePath) {
    std::ifstream infile(filePath);
    std::string fileContents((std::istreambuf_iterator<char>(infile)),
                             (std::istreambuf_iterator<char>()));
    
    return fileContents;
}

Shader::Shader(const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath) {
    
    // Retrieve the vertex and fragment source code
    std::string vertexShaderFileContents = readFile(vertexShaderPath);
    std::string fragmentShaderFileContents = readFile(fragmentShaderPath);
    
    const GLchar *vertexShaderCode = vertexShaderFileContents.c_str();
    const GLchar *fragmentShaderCode = fragmentShaderFileContents.c_str();
    
    // Compile shaders
    GLuint vertexShader, fragmentShader;
    GLint success;
    GLchar infoLog[512];
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }
    
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(program);
}
