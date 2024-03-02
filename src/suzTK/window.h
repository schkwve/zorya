/**
 * @file utils/logging.h
 * @author lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief Utility for window management
 */
#ifndef SUZTK_WINDOW_H
#define SUZTK_WINDOW_H

#include <SDL2/SDL.h>
#include <stdint.h>

struct suztk_window {
  SDL_Renderer *renderer;

  SDL_Window *window;
  uint32_t flags;

  int width;
  int height;
  uint8_t is_fullscreen;
};

struct suztk_winman {
  struct suztk_window *windows;
  size_t window_count;

  int current_window;
};

int suzwin_create_window(int width, int height, uint8_t fullscreen, const char *title);

void suzwin_render_current_window(void);
void suzwin_destroy_current_window(void);

#endif /* SUZTK_WINDOW_H  */
