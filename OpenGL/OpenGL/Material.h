#pragma once
#include "Header.h"

static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform vec3 color;\n"
"uniform vec3 gloabalLightColor;\n"
"uniform float globalLightPower;\n"
"attribute vec3 vPos;\n"
"out vec3 colorTR;\n"

"void main()\n"
"{\n"
"    gl_Position = vec4(vPos, 1.0);\n"//projection * view *
"    colorTR= gloabalLightColor * color * globalLightPower;"
"}\n";

//


static const char*  fragment_shader_text =
"#version 330 core\n"
"in vec3 colorTR;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"    Color = vec4(colorTR, 1.0);\n"
"}\n";


class Material
{
private:
    GLuint squad_vertex_buffer, vertex_shader, fragment_shader, program;

public:
    vec3 color;
    float specular;
    float specular_routhness;

public: 
    Material(vec3 color, float specular, float specular_roth) {
        vec3_dup(this->color, color);
        this->specular = specular;
        this->specular_routhness = specular_roth;
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

