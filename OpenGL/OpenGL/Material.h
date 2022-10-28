#pragma once
#include "Header.h"
class Material
{
private:
	const char* vertex_shader_text;
	const char* fragment_shader_text;
    
	GLuint program;

public:
    vec4 color;

public: 
    Material() {
        
    }

    GLuint CompileShaders() {
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
        glCompileShader(vertex_shader);

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
        glCompileShader(fragment_shader);

        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return program;
	}
};

