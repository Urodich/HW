#pragma once
#include "Header.h"

static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform vec3 color;\n"

"attribute vec3 vNorm;\n"
"attribute vec3 vPos;\n"

"out vec3 colorTR;\n"
"out vec3 Normal;\n"
"out vec3 FragPos;"

"void main()\n"
"{\n"
"    gl_Position = projection * view * MVP * vec4(vPos, 1.0);\n"
"    FragPos = vec3(MVP * vec4(vPos, 1.0));\n"
"    colorTR= color;\n"
"    Normal = vNorm;\n"
"}\n";


static const char* fragment_shader_text =
"#version 330 core\n"
"in vec3 colorTR;\n"
"in vec3 Normal;\n;"
"in vec3 FragPos;\n"

"uniform vec3 globalLightColor;\n"
"uniform float globalLightPower;\n"
"uniform vec3 lightPos;\n"
"uniform float lightPower;\n"
"uniform vec3 viewPos;\n"

"out vec4 Color;\n"
"void main()\n"
"{\n"
//"    vec3 viewDir = normalize(viewPos - FragPos);"
//"    vec3 ambient = globalLightPower * globalLightColor;"
//"    vec3 norm = normalize(Normal);"
//"    vec3 lightDir = normalize(lightPos - FragPos); "
////"    vec3 lightDir = normalize(lightPos); "
//"    float diff = max(dot(norm, lightDir), 0.0);"
//"    vec3 diffuse = diff * globalLightColor * lightPower;"
//"    vec3 reflectDir = reflect(-lightDir, Normal); "
//"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);"
//"    vec3 specular = 0.5 * spec * globalLightColor;"
//"    vec3 result = (ambient + diffuse + specular) * colorTR;"
//"    Color = vec4(result, 1.0);\n"
"Color = vec4(1.0,1.0,1.0,1.0);"
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

