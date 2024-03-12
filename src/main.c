/**
 * @file main.c
 * @author lolguy91 <retek1544@gmail.com>, KapPetrov
 * <xicreationsofficial@gmail.com>
 * @date 29/02/2024
 * @brief Main file
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
 * @brief Checks if user clicked on button
 * @param x
 *          mouse x
 * @param y
 *          mouse y
 * @param rect
 *          button
*/
bool pointInsideRect(int x, int y, SDL_Rect rect) 
{
    return (x >= rect.x && x < (rect.x + rect.w) && y >= rect.y && y < (rect.y + rect.h));
}

/**
 * @brief Browser entry point.
 */
int main(void)
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
    // initialize SDL_Ttf
    status = TTF_Init();
    if (status != 0) {
        log_fatal("SDL_TTF failed to initialize: %s", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

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
            if (event.type == SDL_QUIT) {
                should_quit = true;
            }

            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Check if mouse click is inside the button
                /*if (pointInsideRect(mouseX, mouseY, {SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2, BUTTON_WIDTH, BUTTON_HEIGHT})) {
                    printf("test\n");
                }*/
            }
        }
        if (!browser_update()) {
            log_fatal("Failed to update browser.");
            should_quit = true;
        }
    }

    browser_destroy();

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
