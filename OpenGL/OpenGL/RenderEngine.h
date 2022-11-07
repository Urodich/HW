#pragma once
#include "Header.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include <vector>
#include <thread>

using namespace std;

static Vertices squad[] = {
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


class RenderEngine
{
private:
    vector<Object*> Objects;
    vector<Material*> Materials;
    vector<Light*> Lights;

    static RenderEngine* Eng;
public:
    Camera* camera;
    GLFWwindow* window;
    int width, height;
    vec3 gloabal_light_color = {0.5f,0.5f,0.5};
    float gloabal_light_power=0.5f;
private:
    void init() {

        glfwSetErrorCallback(error_callback);


        if (!glfwInit())
            exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        window = glfwCreateWindow(640, 480, "Lab4", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);
        gladLoadGL();
        glfwSwapInterval(1);
        glfwGetFramebufferSize(window, &width, &height);

    }

    void UpdateObject(Object* object) {
        object->UseShader(camera->projection, camera->look_at, gloabal_light_color, gloabal_light_power);
    }

    void Update() {
        glViewport(0, 0, width, height);
        glClearColor(gloabal_light_color[0], gloabal_light_color[1], gloabal_light_color[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->UpdateCamera();

        for (Object* object : Objects){
            UpdateObject(object);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_P)
            if (action == GLFW_PRESS)
            {
                perspective = !perspective;
                printf("changed view\n");
            }
        if (key == GLFW_KEY_A)
            if (action == GLFW_PRESS)
            {
                Add(Eng);
                printf("added object\n");
            }

        if (key == GLFW_KEY_DOWN) {
            printf("down\n");
            if (action == GLFW_PRESS)
                moving_direction_y -= 1;
            if (action == GLFW_RELEASE)
                moving_direction_y += 1;
        }
        if (key == GLFW_KEY_UP) {
            printf("up\n");
            if (action == GLFW_PRESS)
                moving_direction_y += 1;
            if (action == GLFW_RELEASE)
                moving_direction_y -= 1;
        }
        if (key == GLFW_KEY_LEFT) {
            printf("left\n");
            if (action == GLFW_PRESS)
                moving_direction_x -= 1;
            if (action == GLFW_RELEASE)
                moving_direction_x += 1;
        }
        if (key == GLFW_KEY_RIGHT) {
            printf("right\n");
            if (action == GLFW_PRESS)
                moving_direction_x += 1;
            if (action == GLFW_RELEASE)
                moving_direction_x -= 1;
        }

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    void Work() {
        while (!glfwWindowShouldClose(window)) {
            Update();
        }

        glfwDestroyWindow(window);

        glfwTerminate();
        exit(EXIT_SUCCESS);
        printf("Destroy RE\n");
    }

    RenderEngine() {
        camera = NULL;
        init();
        glfwSetKeyCallback(window, key_callback);
        AddCamera();
        printf("Create RE\n");
        Materials.push_back(new Material(new vec3 {1,1,1}, 0.5f, 32));
    }
public:
    static RenderEngine* GetInstance() {
        if (Eng == NULL) {
            Eng = new RenderEngine();
    }
        return Eng;
    }
    void Start() {
        Work();
    }
    void AddCamera() {
        camera = new Camera(window);
    }
    Material* CreateMaterial(vec3 color, float specular, float specular_routhness) {
        
        Materials.push_back(new Material(color, specular, specular_routhness));
        return Materials.back();
    }
    Object* AddObject(Vertices* model) {
        vec3 pos = { 0,0,0 };
        vec3 color = { 1,1,1 };
        if(Materials.size() == 0)
            Materials.push_back(new Material(color, 0.5f, 32));

        Object* obj = new Object(Materials[0], pos, model);
        Objects.push_back(obj);
        return obj;
    }
    void MoveObject(Object object, vec3 dir) {
        vec3_add(object.position, object.position, dir);
    }
    static void Add(RenderEngine* eng) {
        eng->AddObject(squad);
    }

};




