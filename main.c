#include "engine.h"
#include "window.h"

#include <stdio.h>
#include <getopt.h>

void
print_help (void) {
    printf("Usage: lg [options...]\n");
    printf("Options:\n");
    printf("\t-s, --size\tsize field\n");
    printf("\t-f, --fill\tfill field\n");
    printf("\t-d, --delay\tdelay step\n");
    printf("\t-h, --help\tfor information to commands\n");
}

int
main (int argc, char *argv[]) {
    /* parse args */
    int size =  100;
    int fill =  30;
    int delay = 1000000;

    const char short_options[] = "s:f:d:h";

    const struct option long_options[] = {
        {"size",  required_argument, NULL, 's'},
        {"fill",  required_argument, NULL, 'f'},
        {"delay", required_argument, NULL, 'd'},
        {"help",  no_argument,       NULL, 'h'},
        {NULL,    0,                 NULL, 0}
    };

    int res;
    int option_index;
    while ((res = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (res){
            case 's': size = atoi(optarg);  break;
            case 'f': fill = atoi(optarg);  break;
            case 'd': delay = atoi(optarg); break;
            case 'h':
                print_help();
                return EXIT_SUCCESS;
            case '?': default:
                printf("found unknown option\n");
                return EXIT_SUCCESS;
        }
    }

    /* game */
    ENGINE *engine = engine_init(size, fill, delay);
    if (engine == NULL) {
        fprintf(stderr, "error: engine_init");
        return EXIT_FAILURE;
    }

    WINDOW *window = window_init(512, 512, "LIFE GAME");
    if (window == NULL) {
        fprintf(stderr, "error: window_init");
        return EXIT_FAILURE;
    }

    while (window_is_close(window)) {
        if (window_is_press_key(window, WINDOW_KEY_RESET)) {
            engine_reset(engine);
        } else if (window_is_press_key(window, WINDOW_KEY_QUIT)) {
            engine_finish(engine);
            break;
        }

        window_update(
            window,
            engine_get_size(engine),
            engine_get_field(engine)
        );
    }

    window_free(window);
    engine_free(engine);

    return EXIT_SUCCESS;
}
