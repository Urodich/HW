#include "Header.h"


static float squad[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 2.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 2.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 2.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 2.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 2.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 2.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 2.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 2.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 3.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 3.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 3.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 3.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 3.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 3.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 5.0f, 3.0f,
         0.5f,  0.5f, -0.5f,  5.0f, 5.0f, 3.0f,
         0.5f,  0.5f,  0.5f,  5.0f, 0.0f, 3.0f,
         0.5f,  0.5f,  0.5f,  5.0f, 0.0f, 3.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 3.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 5.0f, 3.0f
};

static struct {
    float x, y, z, a, b;
    int ind;
}
squad1[] = {
        {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1},
        {0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1 },
        {0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1},
        {0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1},
        {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1},
        {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1},

        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1 },
        {0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1},
        {0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1},
        {0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1},
        {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1},
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1},

        {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2},
        {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 2},
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 2},
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 2},
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 2},
        {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2},

        {0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2},
        {0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 2},
        {0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 2},
        {0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 2},
        {0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 2},
        {0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2},

        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 3},
        {0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 3},
        {0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 3},
        {0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 3},
        {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 3},
        {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 3},

        {-0.5f,  0.5f, -0.5f,  0.0f, 5.0f, 3},
        {0.5f,  0.5f, -0.5f,  5.0f, 5.0f, 3},
        {0.5f,  0.5f,  0.5f,  5.0f, 0.0f, 3},
        {0.5f,  0.5f,  0.5f,  5.0f, 0.0f, 3},
        {0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 3},
        {-0.5f,  0.5f, -0.5f,  0.0f, 5.0f, 3}
};

static const char* vertex_shader_text =
"#version 330 core\n"

"uniform mat4 MVP;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"

"out vec2 TexCoord;\n"
//"out float indx;\n"

"layout (location = 0) in vec3 vPos;\n"
"layout (location = 2) in vec2 texCoord;\n"
//"layout (location = 3) in float ind;\n"

"void main()\n"
"{\n"
"    gl_Position = projection * view * MVP * vec4(vPos, 1.0);\n"
"    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n"
//"    indx = ind;\n"
"}\n";

//


static const char* fragment_shader_text =
"#version 330 core\n"

"in vec2 TexCoord;\n"
//"in float indx;\n"
"out vec4 color;\n"

"uniform sampler2D Texture1;\n"
//"uniform sampler2D Texture2;\n"
//"uniform sampler2D Texture3;\n"

"void main()\n"
"{\n"
//"    sampler2D Textures[3]={Texture1, Texture2, Texture3};\n"
//"    int i=int(indx);"  
"    color = texture(Texture1, TexCoord);\n"
"}\n";


static GLFWwindow* window;
static GLuint squad_vertex_buffer, vertex_shader, fragment_shader, program;
static GLint mvp_location, projection_location, texture_indx_location, view_location, vpos_location, vcol_location;


static float ratio, speed = 0.3f, fov = 45.f;
static int width, height;
static mat4x4 m, projection, look_at;

static vec3 cameraX, cameraY, offset, cameraPos = { 0,0,3 }, aim = { 0,0,0 }, up = { 0,1,0 };


 

static void key_callback3(GLFWwindow* window, int key, int scancode, int action, int mods)
{
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

    window = glfwCreateWindow(640, 480, "Lab4", NULL, NULL);
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
//moving
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
    vec3_scale(cameraPos, cameraPos, old/cur);
    mat4x4_look_at(look_at, cameraPos, aim, up);


    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;

    mat4x4_identity(m);
    mat4x4_translate(m, 0, 0, 0);
    mat4x4_ortho(m, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    glfwGetFramebufferSize(window, &width, &height);

    mat4x4_perspective(projection, fov, ratio, 0.1f, 100.0f);
}

GLuint create_texture(const char* path, GLuint &texture) {
    //GLuint texture;
    // ====================
    // Texture 1
    // ====================
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    int width, height;
    unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}


void lab4() {
    moving_direction_x = 0;
    moving_direction_y = 0;

    init();

    GLuint texture1, texture2, texture3;

    create_texture("../OpenGL/textures/1.jpg", texture1);
    create_texture("../OpenGL/textures/4.jpg", texture2);
    create_texture("../OpenGL/textures/3.jpg", texture3);

    glGenBuffers(1, &squad_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, squad_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squad), squad, GL_STATIC_DRAW);

    shaders();

    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "texCoord");
    //texture_indx_location = glGetAttribLocation(program, "ind");

    int tex[] = { 0,1,2 };

    /*glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(program, "Texture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(program, "Texture2"), 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture3);
    glUniform1i(glGetUniformLocation(program, "Texture3"), 2);*/
    //glUniform1iv(glGetUniformLocation(program, "Textures"), 3, tex);
    //glUniform3i(glGetUniformLocation(program, "Textures"), 0,1,2);
    
    
    

    mvp_location = glGetUniformLocation(program, "MVP");
    view_location = glGetUniformLocation(program, "view");
    projection_location = glGetUniformLocation(program, "projection");

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        camera();

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);

        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vcol_location, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(vcol_location);
        //glVertexAttribPointer(texture_indx_location, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(squad[0]), (void*)(5 * sizeof(float)));
        //glEnableVertexAttribArray(texture_indx_location);

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)m);
        glUniformMatrix4fv(view_location, 1, GL_FALSE, (const GLfloat*)look_at);
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, (const GLfloat*)projection);

        glBindBuffer(GL_ARRAY_BUFFER, squad_vertex_buffer);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glDrawArrays(GL_TRIANGLES, 0, 12);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glDrawArrays(GL_TRIANGLES, 0, 24);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}