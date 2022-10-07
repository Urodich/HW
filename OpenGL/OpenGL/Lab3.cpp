#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "./linmath.h"

#include <stdlib.h>
#include <stdio.h>

static const struct
{
    float x, y, z;
    float r, g, b;
} ssquad[8] =
{
    { -0.2f, -0.2f, 0, 1.f, 1.f, 0.f },
    {  0.2f, -0.2f, 0, 0.f, 1.f, 1.f },
    {  0.2f, 0.2f, 0, 1.f, 0.f, 0.f },
    { -0.2f, 0.2f, 0, 0.f, 1.f, 1.f },

    { -0.2f, -0.2f, 1, 1.f, 1.f, 0.f },
    {  0.2f, -0.2f, 1, 0.f, 1.f, 1.f },
    {  0.2f, 0.2f, 1, 1.f, 0.f, 0.f },
    { -0.2f, 0.2f, 1, 0.f, 1.f, 1.f }
};
GLfloat squad[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"attribute vec2 vCol;\n"
"attribute vec3 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * MVP * vec4(vPos, 1.0f);\n"
"    color = vec3(vCol, 0);\n"
"}\n";


static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


int moving_direction_x = 0;
int moving_direction_y = 0;
float fov = 45.f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_DOWN)
        if (action == GLFW_PRESS)
            moving_direction_y -= 1;
    if (action == GLFW_RELEASE)
        moving_direction_y += 1;
    if (key == GLFW_KEY_UP)
        if (action == GLFW_PRESS)
            moving_direction_y += 1;
    if (action == GLFW_RELEASE)
        moving_direction_y -= 1;
    if (key == GLFW_KEY_LEFT)
        if (action == GLFW_PRESS)
            moving_direction_x -= 1;
    if (action == GLFW_RELEASE)
        moving_direction_x += 1;
    if (key == GLFW_KEY_RIGHT)
        if (action == GLFW_PRESS)
            moving_direction_x += 1;
    if (action == GLFW_RELEASE)
        moving_direction_x -= 1;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

int main(void)
{
    GLFWwindow* window;
    GLuint squad_vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, projection_location, view_location, vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);


    if (!glfwInit())
        exit(EXIT_FAILURE);

    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);*/

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    //NOTE: OpenGL error checks have been omitted for brevity

    glGenBuffers(1, &squad_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, squad_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squad), squad, GL_STATIC_DRAW);

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

    //mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    vec3 cameraX,cameraY,offset,cameraPos = { 0,0,3 };
    vec3 aim = { 0,0,0 };
    vec3 up = { 0,1,0 };
    mat4x4 look_at;



    while (!glfwWindowShouldClose(window))
    {
        //moving
        vec3_mul_cross(cameraX, cameraPos, up);
        vec3_norm(cameraX, cameraX);
        vec3_mul_cross(cameraY, cameraPos, cameraX);
        vec3_norm(cameraY, cameraY);

        vec3_scale(cameraX, cameraX, moving_direction_x);
        vec3_scale(cameraY, cameraY, moving_direction_x);
        
        vec3_add(offset, cameraX, cameraY);
        vec3_add(cameraPos, cameraPos, offset);
        
        mat4x4_look_at(look_at, cameraPos, aim, up);

        float ratio;
        int width, height;
        mat4x4 m, projection;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        mat4x4_identity(m);
        //mat4x4_ortho(m, -1.f, 1.f, -1.f, 1.f, 1.f, -1.f);

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        mat4x4_perspective(projection, fov, width / height, 0.1f, 100.0f);

        /*mat4x4_mul(projection, projection, look_at);
        mat4x4_mul(m, projection, m);*/

        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);

        mvp_location = glGetUniformLocation(program, "MVP");
        view_location = glGetUniformLocation(program, "view");
        projection_location = glGetUniformLocation(program, "projection");

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)m);
        glUniformMatrix4fv(view_location, 1, GL_FALSE, (const GLfloat*)look_at);
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, (const GLfloat*)projection);
        
         
        glBindBuffer(GL_ARRAY_BUFFER, squad_vertex_buffer);
        /*glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(squad[0]), (void*)0);
        glEnableVertexAttribArray(vcol_location);
        glVertexAttribPointer(vcol_location, 2, GL_FLOAT, GL_FALSE, sizeof(squad[0]), (void*)(sizeof(float) * 3));*/

        // Position attribute
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(vpos_location);
        // TexCoord attribute
        glVertexAttribPointer(vcol_location, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(vcol_location);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisableVertexAttribArray(vpos_location);
        glDisableVertexAttribArray(vcol_location);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


