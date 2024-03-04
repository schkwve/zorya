/**
 * @file suzTK/window.h
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 29/02/2024
 * @brief Window utilities
 */
#ifndef SUZTK_WINDOW_H
#define SUZTK_WINDOW_H

#include <SDL.h>
#include <stdint.h>

/**
 * @brief Window structure
 *
 * This structure holds all important information about a window.
 */
struct suztk_window
{
    SDL_Window *window;
    uint32_t flags;

    SDL_Renderer *renderer;
    SDL_Surface *surface;

    int width;
    int height;
    uint8_t is_fullscreen;
};

struct suztk_window *
suzwin_create_window(int width,
                     int height,
                     uint8_t fullscreen,
                     const char *title);
void
suzwin_destroy_window(struct suztk_window *win);

void
suzwin_set_title(struct suztk_window *win, const char *title);
void
suzwin_set_icon(struct suztk_window *win, const char *iconpath);

void
suzwin_render(struct suztk_window *win);

#endif /* SUZTK_WINDOW_H  */
