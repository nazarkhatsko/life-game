#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    int size;
    bool **field;
    int fill;
    int delay;
    pthread_t thread;
} ENGINE;

ENGINE * engine_init      (int size, int fill, int delay);
int      engine_get_size  (ENGINE *engine);
bool **  engine_get_field (ENGINE *engine);
void     engine_start     (ENGINE *engine);
void     engine_reset     (ENGINE *engine);
void     engine_finish    (ENGINE *engine);
void     engine_free      (ENGINE *engine);
