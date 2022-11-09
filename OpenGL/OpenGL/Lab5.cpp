#include "Header.h"
#include <vector>
#include <math.h>

//using namespace std;

static float squad[] = {
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

struct Vertices {
    float x, y, z;
    float Nx, Ny, Nz;
};
static Vertices squad1[] = {
    {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.f},
    {0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.f},
    {0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.f},
    {0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.f},
    {-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.f},
    {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.f},

    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.f},
    {0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.f},
    {0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.f},
    {0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.f},
    {-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.f},
    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.f},

    {-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f},
    {-0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f},
    {-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f},
    {-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f},
    {-0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f},
    {-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f},

    {0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f},
    {0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f},
    {0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f},
    {0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f},
    {0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f},
    {0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f},

    {-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f},
    {0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f},
    {0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f},
    {0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f},
    {-0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f},
    {-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f},

    {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f},
    {0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f},
    {0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f},
    {0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f},
    {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f},
    {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f}
};

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

//


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
"    vec3 viewDir = normalize(viewPos - FragPos);"
"    vec3 ambient = globalLightPower * globalLightColor;"
"    vec3 norm = normalize(Normal);"
//"    vec3 lightDir = normalize(lightPos - FragPos); "
"    vec3 lightDir = normalize(lightPos); "
"    float diff = max(dot(norm, lightDir), 0.0);"
"    vec3 diffuse = diff * globalLightColor * lightPower;"
"    vec3 reflectDir = reflect(-lightDir, Normal); "
"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);"
"    vec3 specular = 0.5 * spec * globalLightColor;"
"    vec3 result = (ambient + diffuse + specular) * colorTR;"
"    Color = vec4(result, 1.0);\n"
"}\n";

static std::vector<float> sphereVertices;
std::vector<int> sphereIndices;

const GLfloat PI = 3.14159265358979323846f;
// Разделим мяч по горизонтали и вертикали на сетку 50 * 50
const int Y_SEGMENTS = 50;
const int X_SEGMENTS = 50;

static GLFWwindow* window;
static GLuint squad_vertex_buffer, vertex_shader, fragment_shader, program;
static GLint mvp_location, projection_location, view_location, vpos_location, vcol_location;
static bool perspective = true;

static float ratio, speed = 0.3f, fov = 45.f;
static int width, height;
static mat4x4 m, projection, look_at;

static vec3 cameraX, cameraY, offset, lightPos = {2, 2, 4}, cameraPos = { 0,0,3 }, aim = { 0,0,0 }, up = { 0,1,0 };


static void key_callback3(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_P)
        if (action == GLFW_PRESS)
            perspective = !perspective;

    if (key == GLFW_KEY_DOWN) {
        if (action == GLFW_PRESS)
            moving_direction_y -= 1;
        if (action == GLFW_RELEASE)
            moving_direction_y += 1;
    }
    if (key == GLFW_KEY_UP) {
        if (action == GLFW_PRESS)
            moving_direction_y += 1;
        if (action == GLFW_RELEASE)
            moving_direction_y -= 1;
    }
    if (key == GLFW_KEY_LEFT) {
        if (action == GLFW_PRESS)
            moving_direction_x -= 1;
        if (action == GLFW_RELEASE)
            moving_direction_x += 1;
    }
    if (key == GLFW_KEY_RIGHT) {
        if (action == GLFW_PRESS)
            moving_direction_x += 1;
        if (action == GLFW_RELEASE)
            moving_direction_x -= 1;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset / 20;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

static void init() {
    glfwSetErrorCallback(error_callback);


    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Lab5", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback3);
    glfwSetScrollCallback(window, scroll_callback);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);
}

static void shaders() {
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
}

static void camera() {
    vec3_mul_cross(cameraX, cameraPos, up);
    vec3_norm(cameraX, cameraX);
    vec3_mul_cross(cameraY, cameraPos, cameraX);
    vec3_norm(cameraY, cameraY);

    vec3_scale(cameraX, cameraX, moving_direction_x * speed);
    vec3_scale(cameraY, cameraY, moving_direction_y * speed);

    vec3_add(offset, cameraX, cameraY);

    float old = vec3_len(cameraPos);
    vec3_add(cameraPos, cameraPos, offset);
    float cur = vec3_len(cameraPos);
    vec3_scale(cameraPos, cameraPos, old / cur);
    mat4x4_look_at(look_at, cameraPos, aim, up);

    mat4x4_look_at(look_at, cameraPos, aim, up);


    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;

    mat4x4_identity(m);
    mat4x4_translate(m, 0, 0, 0);
    mat4x4_ortho(m, -1, 1, -1.f, 1.f, 1.f, -1.f);

    glfwGetFramebufferSize(window, &width, &height);

    const float aspect = (float)width / (float)height;
    if (!perspective) mat4x4_ortho(projection, -1.0f, 1.0, -aspect, aspect, 0.1f, 100.0f);
    else mat4x4_perspective(projection, fov, ratio, 0.1f, 100.0f);
}

static void createSphere() {
    for (int y = 0; y <= Y_SEGMENTS; y++)
    {
        for (int x = 0; x <= X_SEGMENTS; x++)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = cos(xSegment * 2.0f * PI) * sin(ySegment * PI);
            float yPos = cos(ySegment * PI);
            float zPos = sin(xSegment * 2.0f * PI) * sin(ySegment * PI);
            sphereVertices.push_back(xPos);
            sphereVertices.push_back(yPos);
            sphereVertices.push_back(zPos);
        }
    }

    // Индексы, генерирующие мяч
    for (int i = 0; i < Y_SEGMENTS; i++)
    {
        for (int j = 0; j < X_SEGMENTS; j++)
        {
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
        }
    }
}

void lab5(void)
{
    moving_direction_x = 0;
    moving_direction_y = 0;


    init();

    createSphere();

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Генерация и привязка VAO и VBO сферы
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Привязываем данные вершины к текущему буферу по умолчанию
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), &sphereVertices[0], GL_STATIC_DRAW);

    GLuint element_buffer_object;//EBO
    glGenBuffers(1, &element_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(int), &sphereIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

   /* glGenBuffers(1, &squad_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, squad_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(Vertices), squad1, GL_STATIC_DRAW);*/

    shaders();

    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vNorm");


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.6,0.6,0.6, 1.0f);
        //moving
        camera();

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(squad1[0]), (void*)0);
        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(squad1[0]), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(vcol_location);

        glUniform3f(glGetUniformLocation(program, "color"), 0.3f, 1.f, 0.7f);
        glUniform1f(glGetUniformLocation(program, "globalLightPower"), 0.4f);
        glUniform3f(glGetUniformLocation(program, "globalLightColor"), 1.f, 0.6f, 0.3f);

        glUniform3f(glGetUniformLocation(program, "lightPos"), 0.f, 4.f, 0.f);
        glUniform1f(glGetUniformLocation(program, "lightPower"), 0.8f);
        glUniform3f(glGetUniformLocation(program, "viewPos"), cameraPos[0], cameraPos[1], cameraPos[2]);

        glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, GL_FALSE, (const GLfloat*)m);
        glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, (const GLfloat*)look_at);
        glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, (const GLfloat*)projection);

        //glDrawArrays(GL_TRIANGLES, 0, 36);
        glDrawElements(GL_TRIANGLES, X_SEGMENTS * Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


