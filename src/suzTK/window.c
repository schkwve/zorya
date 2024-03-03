/**
 * @file utils/logging.h
 * @author lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief window management implementation
 */

#include <SDL.h>
#include <SDL_image.h>

#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include <utils/logging.h>
#include "window.h"

//static struct suztk_winman window_manager = {0};

static struct suztk_window window = {0};

int suzwin_create_window(int width, int height, uint8_t fullscreen, const char *title)
{
    uint32_t flags = SDL_WINDOW_RESIZABLE;
    if (!!fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    SDL_Window *win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if (win == NULL) {
        log_error("SDL_CreateWindow returned NULL! %s", SDL_GetError());
        return -1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        log_error("SDL_CreateRenderer returned NULL! %s", SDL_GetError());
        SDL_DestroyWindow(win);
        return -1;
    }

    /*
    size_t window_count = window_manager.window_count;

    struct suztk_window *new = &window_manager.windows[window_count];
    new = (struct suztk_window *)malloc(sizeof(struct suztk_window *));
    if (new == NULL) {
        log_error("Failed to malloc() new window: %s!", strerror(errno));
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        return -1;
    }

    new->window = win;
    new->renderer = ren;
    new->flags = flags;
    new->width = width;
    new->height = height;
    new->is_fullscreen = !!fullscreen;

    window_manager.current_window = window_manager.window_count;
    window_manager.window_count++;

    SDL_RenderPresent(new->renderer);
    */

    window.window = win;
    window.renderer = ren;
    window.flags = flags;
    window.width = width;
    window.height = height;
    window.is_fullscreen = !!fullscreen;

    SDL_RenderPresent(window.renderer);

    return 0;
}

/**
 * @brief Updates the window's title with a new one
 *
 * @param title
 *        New window title
 */
void suzwin_set_title(const char *title)
{
    SDL_SetWindowTitle(window.window, title);
}

/**
 * @brief Sets the window's icon.
 *
 * @param iconpath
 *        Path to an icon file
 */
void suzwin_set_icon(const char *iconpath)
{
    SDL_SetWindowIcon(window.window, NULL);
}

void suzwin_render_current_window(void)
{
    //SDL_RenderPresent(window_manager.windows[window_manager.current_window].renderer);
    SDL_RenderPresent(window.renderer);
}

void suzwin_destroy_current_window(void)
{
    /*
    int curwin = window_manager.current_window;

    if (window_manager.windows[curwin].renderer == NULL) {
        SDL_DestroyRenderer(window_manager.windows[curwin].renderer);
    }
    SDL_DestroyWindow(window_manager.windows[curwin].window);
    free(&window_manager.windows[curwin]);
    window_manager.window_count--;
    */
}
