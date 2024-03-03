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

#include <suzTK/window.h>
#include <core/browser.h>
#include <netwerk/connect.h>
#include <netwerk/http.h>
#include <utils/buffer.h>
#include <string.h>

#include "utils/logging.h"
#include "antiralsei/parse.h"
#include "antiralsei/handler.h"

#include "UI/homepage.h"


int
main(void)
{
    int status = 0;

    // initialize SDL
    status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (status != 0) {
        log_fatal("SDL failed to initialize! (return code: %d)", status);
        return -1;
    }

    int sdlimg_flags = IMG_INIT_PNG;
    if ((IMG_Init(sdlimg_flags) & sdlimg_flags) != sdlimg_flags) {
        log_fatal("SDL_Image failed to initialize!");
        SDL_Quit();
        return -1;
    }

    // create a window
    suzwin_create_window(1280, 720, 0, "I can't spell the name of this fucking browser");

    // initialize browser
    if (!browserInit()) {
        log_fatal("Failed to initialize browser.");
        return -1;
    }

    bool should_quit = false;
    SDL_Event event;

    // browser loop
    while (should_quit != true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                should_quit = true;
            }
        }
    }

    browserDestroy();

    IMG_Quit();
    SDL_Quit();

    return 0;
}
