#pragma once
#define GLFW_INCLUDE_NONE


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include "../SOIL/inc/SOIL/SOIL.h"

static int moving_direction_x;
static int moving_direction_y;
static int rotation;

void lab1();
void lab2();
void lab3();
void lab4();

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
};