/**
 * @file components/text.c
 * @author Jozef Nagy <schkwve@gmail.com>
 * @date 04/03/2024
 * @brief Text rendering component
 */

#include <assert.h>
#include <stdlib.h>

#include <SDL.h>
#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_LCD_FILTER_H
#include <freetype/ftadvanc.h>
#include <freetype/ftsnames.h>
#include <freetype/tttables.h>

#include <hb-ft.h>
#include <hb-glib.h>
#include <hb.h>

#include <cairo-ft.h>
#include <cairo.h>

#include "text.h"
#include <suzTK/window.h>
#include <utils/logging.h>

static struct component_text comp;

/**
 * @brief Initializes the text component.
 *
 * @param name
 *        Font name to look for
 *
 * @param size
 *        Font size
 */
void
component_text_init(char *name, int size)
{
    FcInit();
    FcConfig *config = FcInitLoadConfigAndFonts();
    assert(config);

    // Look for FreeMono font
    FcPattern *pat = FcNameParse((const FcChar8 *)name);

    FcConfigSubstitute(config, pat, FcMatchPattern);
    FcDefaultSubstitute(pat);

    FcResult result;
    FcPattern *font = FcFontMatch(config, pat, &result);
    assert(font);

    FcChar8 *file = NULL;
    assert(FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch);

    // initialize freetype
    assert(!FT_Init_FreeType(&comp.ft_library));

    FT_Library_SetLcdFilter(comp.ft_library, FT_LCD_FILTER_DEFAULT);

    assert(!FT_New_Face(comp.ft_library, (char *)file, 0, &comp.ft_face));
    assert(!FT_Set_Char_Size(comp.ft_face, 0, size * 64, 0, 0));

    // cleanup
    FcPatternDestroy(font);
    FcPatternDestroy(pat);
    FcConfigDestroy(config);
    FcFini();

    comp.cairo_face = cairo_ft_font_face_create_for_ft_face(comp.ft_face, 0);

    comp.hb_font = hb_ft_font_create(comp.ft_face, NULL);
    comp.hb_face = hb_ft_face_create(comp.ft_face, NULL);

    comp.font_size = size;
}

/**
 * @brief Destroys the text component. Use this on exit only.
 */
void
component_text_destroy(void)
{
    cairo_font_face_destroy(comp.cairo_face);
    hb_font_destroy(comp.hb_font);
    hb_face_destroy(comp.hb_face);
    FT_Done_FreeType(comp.ft_library);
}

/**
 * @brief Renders text on the screen.
 *
 * @param win
 *        Pointer to a window to which text will be rendered
 *
 * @param x
 *        X position
 *
 * @param y
 *        Y position
 *
 * @param color
 *        Text color. Format: 0xAARRGGBB
 *
 * @param text
 *        Text which will be rendered
 *
 * @param direction [optional]
 *        Text direction. If equal to zero, HB_DIRECTION_LTR will
 *        be used by default. Possible values:
 *              - HB_DIRECTION_LTR (left-to-right)
 *              - HB_DIRECTION_RTL (right-to-left)
 *              - HB_DIRECTION_TTB (top-to-bottom)
 *              - HB_DIRECTION_BTT (bottom_to_top)
 *
 * @param script [optional]
 *        Script to use. If equal to zero, HB_SCRIPT_LATIN will
 *        be used by default. Possible values:
 *              - HB_SCRIPT_LATIN
 *              - HB_SCRIPT_ARABIC
 *              - HB_SCRIPT_HAN
 */
void
component_text_render(struct suztk_window *win,
                      int x,
                      int y,
                      uint32_t color,
                      const char *text,
                      int direction,
                      int script)
{
    if (direction == 0) {
        direction = HB_DIRECTION_LTR;
    }
    if (script == 0) {
        script = HB_SCRIPT_LATIN;
    }

    hb_buffer_t *hb_buf = hb_buffer_create();

    // create a nice cairo surface uwu :3
    cairo_surface_t *cairo_surface =
        cairo_image_surface_create_for_data((uint8_t *)win->surface->pixels,
                                            CAIRO_FORMAT_RGB24,
                                            win->surface->w,
                                            win->surface->h,
                                            win->surface->pitch);
    cairo_t *cr = cairo_create(cairo_surface);

    hb_buffer_set_unicode_funcs(hb_buf, hb_glib_get_unicode_funcs());
    hb_buffer_set_direction(hb_buf, direction);
    hb_buffer_set_script(hb_buf, script);
    // maybe add this as a parameter?
    hb_buffer_set_language(hb_buf, hb_language_from_string("en", -1));

    // layout the text
    hb_buffer_add_utf8(hb_buf, text, strlen(text), 0, strlen(text));
    hb_shape(comp.hb_font, hb_buf, NULL, 0);

    // let cairo do its magic *~
    uint32_t glyph_count;
    hb_glyph_info_t *glyph_info =
        hb_buffer_get_glyph_infos(hb_buf, &glyph_count);
    hb_glyph_position_t *glyph_pos =
        hb_buffer_get_glyph_positions(hb_buf, &glyph_count);
    cairo_glyph_t *cairo_glyphs = malloc(sizeof(cairo_glyph_t) * glyph_count);

    uint32_t string_width_px = 0;
    for (int i = 0; i < glyph_count; ++i) {
        string_width_px += glyph_pos[i].x_advance / 64;
    }

    for (int i = 0; i < glyph_count; ++i) {
        cairo_glyphs[i].index = glyph_info[i].codepoint;
        cairo_glyphs[i].x = x + (glyph_pos[i].x_offset / 64.0);
        cairo_glyphs[i].y = y + (glyph_pos[i].y_offset / 64.0);
        x += glyph_pos[i].x_advance / 64.0;
        y -= glyph_pos[i].y_advance / 64.0;
    }

    double r = ((color >> 24) & 0xFF) / 255.0;
    double g = ((color >> 16) & 0xFF) / 255.0;
    double b = ((color >> 8) & 0xFF) / 255.0;
    double a = (color & 0xFF) / 255.0;
    log_debug("R: %f | G: %f | B: %f | A: %f", r, g, b, a);
    cairo_set_source_rgba(cr, r, g, b, a);
    cairo_set_font_face(cr, comp.cairo_face);
    cairo_set_font_size(cr, comp.font_size);
    cairo_show_glyphs(cr, cairo_glyphs, glyph_count);

    free(cairo_glyphs);
    hb_buffer_destroy(hb_buf);

    suzwin_render(win);

    cairo_surface_destroy(cairo_surface);
    cairo_destroy(cr);
}
