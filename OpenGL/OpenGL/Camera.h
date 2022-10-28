#pragma once
#include "Header.h"
#include "RenderEngine.h"
class Camera
{
private:
    GLFWwindow* window;
    vec3 cameraX, cameraY, offset, cameraPos = { 0,0,3 }, aim = { 0,0,0 }, up = { 0,1,0 };
    float ratio,  speed = 0.3f, fov = 45.f;
    bool perspective = true;
public:
    int width, height;
    vec3 Position = { 0,3,3 };
    vec3 Direction;
    mat4x4 projection, look_at;
    
private:
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
public:
    Camera(GLFWwindow* window) {
        this->window = window;
        glfwSetKeyCallback(window, key_callback3);
        glfwSetScrollCallback(window, scroll_callback);
    }

    void UpdateCamera() {
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
        vec3_add(aim, cameraPos, Direction);
        mat4x4_look_at(look_at, cameraPos, aim, up);
        
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        if (!perspective) mat4x4_ortho(projection, -1.0f, 1.0, -ratio, ratio, 0.1f, 100.0f);
        else mat4x4_perspective(projection, fov, ratio, 0.1f, 100.0f);
    }
};

