//
//  shader.hpp
//  Tinker2D
//
//  Created by Abed on 2016-06-21.
//
//

#ifndef shader_hpp
#define shader_hpp

typedef char GLchar;
typedef unsigned int uint32_t;
typedef uint32_t GLuint;

class Shader {
public:
    
    // Build a new shader object using the given vertex and fragment shaders
    Shader(const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath);
    
    // Install this shader's program object as part of the current rendering state
    void use();
private:
    
    // The shader program's ID
    GLuint program;
};

#endif /* shader_hpp */
