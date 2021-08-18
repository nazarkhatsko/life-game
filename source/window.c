#include "window.h"

static void
window_scroll_callback (GLFWwindow *glfw, double xoffset, double yoffset) {
    double n = 0.1;
    if (yoffset > 0) {
        glScalef(1.0 + n, 1.0 + n, 0);
    } else {
        glScalef(1.0 - n, 1.0 - n, 0);
    }
}

static void
window_draw_field (WINDOW *window, int size, bool **field) {
    double x = -1.0;
    double y = -1.0;
    double step = 2.0 / size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (field[i][j]) {
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_POLYGON);
                    glVertex2f(x,        y);
                    glVertex2f(x + step, y);
                    glVertex2f(x + step, y + step);
                    glVertex2f(x,        y + step);
                glEnd();
            }
            y += step;
        }
        y = -1.0;
        x += step;
    }
}

WINDOW *
window_init (int width, int height, char title[]) {
    if (!glfwInit()) {
        return NULL;
    }

    WINDOW *window = malloc(sizeof (*window));

    window->glfw = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window->glfw == NULL) {
        return NULL;
    }

    glfwMakeContextCurrent(window->glfw);
    glfwSetScrollCallback(window->glfw, window_scroll_callback);

    return window;
}

bool
window_is_press_key (WINDOW *window, char key) {
    return glfwGetKey(window->glfw, key) == GLFW_PRESS;
}

bool
window_is_close (WINDOW *window) {
    return !glfwWindowShouldClose(window->glfw);
}

void
window_update (WINDOW *window, int size, bool **field) {
    /* glear buffer OpenGL */
    glClear(GL_COLOR_BUFFER_BIT);

    /* update */
    window_draw_field(window, size, field);

    /* swap bufers OpenGL */
    glfwPollEvents();
    glfwSwapBuffers(window->glfw);
}

void
window_free (WINDOW *window) {
    glfwDestroyWindow(window->glfw);
    glfwTerminate();
    free(window);
}
