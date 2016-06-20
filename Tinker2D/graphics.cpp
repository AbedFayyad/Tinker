
//
//  graphics.cpp
//  Tinker2D
//
//  Created by Abed on 2016-06-20.
//
//

#include "graphics.hpp"

#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>
#include "globals.hpp"
#include "sprite.hpp"

// TODO: remove me
const GLchar *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main() {\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main() {\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};
const GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};

Graphics::Graphics() {
    
    // Set all OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // Create a window
    window = SDL_CreateWindow("Tinker2D",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed %s\n", SDL_GetError());
    }
    
    // Create an OpenGL context
    glcontext = SDL_GL_CreateContext(window);
    if (!glcontext) {
        fprintf(stderr, "SDL_GL_CreateContext failed %s\n", SDL_GetError());
    }
    
    // TODO: use SDL_GL_GetAttribute() to check the values after creating the OpenGL context (the values obtained can differ from the requested ones)
    
    // Build and compile our shader program (with error checking)
    GLint success;
    GLchar infoLog[512];
    
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }
    
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }
    
    // Link shaders (with error checking)
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    
    // Once the shaders are linked they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // Set up buffers and attribute pointers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind the Vertex Array Object first
    glBindVertexArray(VAO);
    
    // Bind and set vertex buffer(s) and attribute pointer(s)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    // glVertexAttribPointer registered VBO as the currently bound vertex buffer object so we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Unbind to prevent mistaken reconfiguration
    glBindVertexArray(0);
    
    // Uncommenting the following line will result in wireframe polygons
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Graphics::~Graphics() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    SDL_DestroyWindow(window);
    
    SDL_GL_DeleteContext(glcontext);
}

void Graphics::draw() {
    
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    // Swaps front and back buffers
    SDL_GL_SwapWindow(window);
}