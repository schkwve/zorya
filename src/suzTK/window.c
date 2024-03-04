/**
 * @file suzTK/window.c
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 29/02/2024
 * @brief Window utilities
 */

#include <SDL.h>
#include <SDL_image.h>

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include "window.h"
#include <utils/logging.h>

/**
 * @brief Creates a new window structure.
 *
 * @param width
 *        Width of the new window
 *
 * @param height
 *        Height of the new window
 *
 * @param fullscreen
 *        Should the window be fullscreen?
 *
 * @param title
 *        Default title to set the window to
 *
 * @return Window pointer if it was created successfully;
 *         NULL otherwise.
 */
struct suztk_window *suzwin_create_window(int width,
                                          int height,
                                          uint8_t fullscreen,
                                          const char *title)
{
    uint32_t flags = SDL_WINDOW_RESIZABLE;
    if (!!fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    struct suztk_window *new =
        (struct suztk_window *)malloc(sizeof(struct suztk_window));
    if (new == NULL) {
        log_error("Failed to allocate memory for a new window!");
        return NULL;
    }

    SDL_Window *win = SDL_CreateWindow(title,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       width,
                                       height,
                                       flags);
    if (win == NULL) {
        log_error("SDL_CreateWindow returned NULL! %s", SDL_GetError());
        free(new);
        return NULL;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        log_error("SDL_CreateRenderer returned NULL! %s", SDL_GetError());
        SDL_DestroyWindow(win);
        free(new);
        return NULL;
    }

    new->window = win;
    new->renderer = ren;
    new->flags = flags;
    new->width = width;
    new->height = height;
    new->is_fullscreen = !!fullscreen;

    suzwin_set_title(new, "Untitled Page");

    SDL_RenderPresent(new->renderer);

    return new;
}

/**
 * @brief Destroys a window object and sets it to NULL.
 *
 * @param win
 *        Window structure to be destroyed
 */
void suzwin_destroy_window(struct suztk_window *win)
{
    assert(win != NULL);
    free(win);
    win = NULL;
}

/**
 * @brief Updates the window's title with a new one
 *
 * @param win
 *        Window structure pointer
 *
 * @param title
 *        New window title
 */
void suzwin_set_title(struct suztk_window *win, const char *title)
{
    assert(win != NULL);

    char *suffix = " • Sovyetski Soyouzy";
    size_t full_title_len = strlen(title) + strlen(suffix) + 1;
    char *full_title = malloc(full_title_len);

    snprintf(full_title, full_title_len, "%s%s", title, suffix);
    SDL_SetWindowTitle(win->window, full_title);
    free(full_title);
}

/**
 * @brief Sets the window's icon.
 *
 * @param win
 *        Window structure pointer
 *
 * @param iconpath
 *        Path to an icon file
 */
void suzwin_set_icon(struct suztk_window *win, const char *iconpath)
{
    assert(win != NULL);
    SDL_Surface *icon = IMG_Load(iconpath);
    SDL_SetWindowIcon(win->window, icon);
}

void suzwin_render_window(struct suztk_window *win)
{
    assert(win != NULL);
    SDL_RenderPresent(win->renderer);
}
