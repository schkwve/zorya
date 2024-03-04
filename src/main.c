/**
 * @file main.c
 * @author lolguy91 <retek1544@gmail.com>, KapPetrov
 * <xicreationsofficial@gmail.com>
 * @date 29/02/2024
 * @brief Main file
 */

#include <SDL.h>
#include <SDL_image.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <components/text.h>
#include <core/browser.h>
#include <netwerk/connect.h>
#include <netwerk/protocols/http.h>
#include <string.h>
#include <suzTK/window.h>
#include <utils/buffer.h>

#include "antiralsei/handler.h"
#include "antiralsei/htmltree.h"
#include "utils/logging.h"

/**
 * @brief Browser entry point.
 */
int
main(void)
{
    int status = 0;
    // initialize SDL
    status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (status != 0) {
        log_fatal("SDL failed to initialize: %s (return code: %d)",
                  SDL_GetError(),
                  status);
        return EXIT_FAILURE;
    }
    // initialize SDL_Image
    status = IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;
    if (status != IMG_INIT_PNG) {
        log_fatal("SDL_Image failed to initialize: %s", IMG_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // initialize browser
    if (!browser_init()) {
        log_fatal("Failed to initialize browser.");
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }
    bool should_quit = false;
    SDL_Event event;

    // browser loop
    while (should_quit != true) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    should_quit = true;
                    break;
                }
                case SDL_WINDOWEVENT: {
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_SIZE_CHANGED: {
                            // width x height
                            // suzwin_handle_resize(event.window.data1,
                            // event.window.data2);
                            break;
                        }
                        case SDL_WINDOWEVENT_CLOSE: {
                            event.type = SDL_QUIT;
                            SDL_PushEvent(&event);
                            break;
                        }
                    }
                }
            }
        }
        if (!browser_update()) {
            log_fatal("Failed to update browser.");
            should_quit = true;
        }

        // just block a bit so we don't spin
        SDL_Delay(150);
    }

    browser_destroy();

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
