/**
 * @file components/text.h
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 04/03/2024
 * @brief Text rendering component
 */

#ifndef COMPONENTS_TEXT_H
#define COMPONENTS_TEXT_H

#include <stdint.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <hb.h>

#include <cairo.h>

#include <suzTK/window.h>

struct component_text
{
    FT_Library ft_library;
    FT_Face ft_face;

    cairo_font_face_t *cairo_face;

    hb_face_t *hb_face;
    hb_font_t *hb_font;

    int font_size;
};

void
component_text_init(char *name, int size);
void
component_text_destroy(void);

void
component_text_render(struct suztk_window *win,
                      int x,
                      int y,
                      uint32_t color,
                      const char *text,
                      int direction,
                      int script);

#endif /* COMPONENTS_TEXT_H */
