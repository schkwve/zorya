/**
 * @file main.c
 * @author lolguy91 <retek1544@gmail.com>, KapPetrov
 * <xicreationsofficial@gmail.com>
 * @date 29/02/2024
 * @brief Main file
 */

#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>

#include <suzTK/window.h>

#include "utils/logging.h"

#include "UI/homepage.h"

bool
browserInit()
{
    return true;
}

bool
browserUpdate()
{
    renderHomePage();

    // TODO: Update
    return true;
}
bool
browserDestroy()
{
    //suzwin_destroy_all_windows();
    suzwin_destroy_current_window();
    return true;
}

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

    SDL_Quit();

    return 0;
}
