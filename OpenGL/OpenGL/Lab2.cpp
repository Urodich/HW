#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../linmath.h"

#include <stdlib.h>
#include <stdio.h>

static const struct
{
    float x, y;
    float r, g, b;
} squad[4] =
{
    { -0.2f, -0.2f, 1.f, 1.f, 0.f },
    {  0.2f, -0.2f, 0.f, 1.f, 1.f },
    {  0.2f, 0.2f, 1.f, 0.f, 0.f },
    { -0.2f, 0.2f, 0.f, 1.f, 1.f }
},
triangle[3] =
{
    { -0.6f, -0.6f, 1.f, 1.f, 0.f },
    {  0.6f, -0.6f, 0.f, 1.f, 1.f },
    {  0, 0.6f, 1.f, 0.f, 0.f }
};

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
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
int rotation = 0;

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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        rotation = 1;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        rotation = -1;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        rotation -= 1;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        rotation -= -1;
}


int main1(void)
{
    GLFWwindow* window;
    GLuint squad_vertex_buffer, triangle_vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);


    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    //NOTE: OpenGL error checks have been omitted for brevity

    glGenBuffers(1, &squad_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, squad_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squad), squad, GL_STATIC_DRAW);

    glGenBuffers(1, &triangle_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    
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

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
    
    

    float speed = 0.01f;
    float offsetX = 0;
    float offsetY = 0;
    float rotate_offset = 0;

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        rotate_offset += rotation * speed * 10;
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, rotate_offset);

        offsetX -= moving_direction_x * speed;
        offsetY -= moving_direction_y * speed;
        mat4x4_ortho(p, -ratio + offsetX, ratio + offsetX, -1.f + offsetY, 1.f + offsetY, 1.f, -1.f);

        //mat4x4_mul(mvp, p, m);
        
        
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)m);

        glBindBuffer(GL_ARRAY_BUFFER, squad_vertex_buffer);
        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(squad[0]), (void*)0);
        glEnableVertexAttribArray(vcol_location);
        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(squad[0]), (void*)(sizeof(float) * 2));

        glDrawArrays(GL_QUADS,0, 4);
        glDisableVertexAttribArray(vpos_location);
        glDisableVertexAttribArray(vcol_location);

        mvp_location = glGetUniformLocation(program, "MVP");
        vpos_location = glGetAttribLocation(program, "vPos");
        vcol_location = glGetAttribLocation(program, "vCol");
        
        glEnableVertexAttribArray(vpos_location);
        glEnableVertexAttribArray(vcol_location);
        glBindBuffer(GL_ARRAY_BUFFER, triangle_vertex_buffer);

        glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(triangle[0]), (void*)0);
        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(triangle[0]), (void*)(sizeof(float) * 2));

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)p);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(vcol_location);
        glDisableVertexAttribArray(vpos_location);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


