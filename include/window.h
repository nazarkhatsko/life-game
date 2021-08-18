#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WINDOW_KEY_RESET 'R'
#define WINDOW_KEY_QUIT  'Q'

typedef struct {
    GLFWwindow *glfw;
} WINDOW;

WINDOW * window_init         (int width, int height, char title[]);
bool     window_is_press_key (WINDOW *window, char key);
bool     window_is_close     (WINDOW *window);
void     window_update       (WINDOW *window, int size, bool **field);
void     window_free         (WINDOW *window);
