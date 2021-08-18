#include "engine.h"

static void *
engine_thread_wrapper (void *arg) {
    ENGINE *engine = (ENGINE *)arg;
    while (true) {
        for (int i = 0; i < engine->size; i++) {
            for (int j = 0; j < engine->size; j++) {
                int n = 0;
                if (i > 0) {
                    n += engine->field[i - 1][j];
                }
                if (i < engine->size - 1) {
                    n += engine->field[i + 1][j];
                }
                if (j > 0) {
                    n += engine->field[i][j - 1];
                }
                if (j < engine->size - 1) {
                    n += engine->field[i][j + 1];
                }
                if (i > 0 && j > 0) {
                    n += engine->field[i - 1][j - 1];
                }
                if (i < engine->size - 1 && j < engine->size - 1) {
                    n += engine->field[i + 1][j + 1];
                }

                if (!engine->field[i][j] && n == 3) {
                    engine->field[i][j] = true;
                } else if (n != 2 && n != 3) {
                    engine->field[i][j] = false;
                }
            }
        }
        usleep(engine->delay);
    }
    return NULL;
}

static bool **
init_field (int size) {
    srand(time(NULL));
    bool **field = malloc(sizeof (*field) * size);
    for (int i = 0; i < size; i++) {
        field[i] = malloc(sizeof (*field[i]) * size);
    }
    return field;
}

static void
rand_field (int size, bool **field, int fill) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            field[i][j] = (rand() % 100) < fill ? true : false;
        }
    }
}

ENGINE *
engine_init (int size, int fill, int delay) {
    ENGINE *engine = malloc(sizeof (*engine));
    engine->size = size;
    engine->fill = fill;
    engine->delay = delay;
    engine->field = init_field(size);
    rand_field(size, engine->field, fill);
    engine_start(engine);
    return engine;
}

int
engine_get_size (ENGINE *engine) {
    return engine->size;
}

bool **
engine_get_field (ENGINE *engine) {
    return engine->field;
}

void
engine_start (ENGINE *engine) {
    pthread_create(&engine->thread, NULL, engine_thread_wrapper, engine);
}

void
engine_reset (ENGINE *engine) {
    engine_finish(engine);
    rand_field(engine->size, engine->field, engine->fill);
    engine_start(engine);
}

void
engine_finish (ENGINE *engine) {
    pthread_cancel(engine->thread);
}

void
engine_free (ENGINE *engine) {
    free(engine->field);
    free(engine);
}
