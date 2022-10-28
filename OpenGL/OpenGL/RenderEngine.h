#pragma once
#include "Header.h"
#include "Object.h"
#include "Camera.h"
#include <vector>

using namespace std;

class RenderEngine
{
private:
    vector<Object> objects;
    Camera* camera;
    
public: 
    GLFWwindow* window;
    int width, height;
private:
    void init() {
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

        glfwMakeContextCurrent(window);
        gladLoadGL();
        glfwSwapInterval(1);
        glfwGetFramebufferSize(window, &width, &height);

    }

    void UpdateObject(Object object) {

    }

    void Update() {
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (Object object : objects)
            UpdateObject(object);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

public:
    void AddCamera() {
        camera = new Camera(window);
    }
    Object* AddObject(float* model, Material material) {
        vec3 pos = { 0,0,0 };
        return new Object(material, pos, model);
    }

    void MoveObject(Object object, vec3 dir) {
        vec3_add(object.position, object.position, dir);
    }

    RenderEngine() {

    }
 
};

