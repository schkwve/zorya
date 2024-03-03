/**
 * @file browser.c
 * @authors Kevin Alavik <kevin@alavik.se>
 *          lolguy91 <retek1544@gmail.com>
 * @date 02/03/2024
 * @brief Source file for core/browser.h
 */

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "browser.h"
#include <antiralsei/handler.h>
#include <antiralsei/parse.h>
#include <netwerk/connect.h>
#include <netwerk/protocols/http.h>
#include <netwerk/resolver.h>
#include <netwerk/url.h>
#include <suzTK/window.h>
#include <utils/buffer.h>
#include <utils/host.h>
#include <utils/logging.h>

#include <UI/home.h>

#define DEFAULT_MONOSPACE_FONT  "../res/freefont/FreeMono.ttf"
#define DEFAULT_SANSSERIF_FONT  "../res/freefont/FreeSans.ttf"
#define DEFAULT_SERIF_FONT      "../res/freefont/FreeSerif.ttf"

#define DEFAULT_MONOSPACE_BOLD_FONT  "../res/freefont/FreeMonoBold.ttf"
#define DEFAULT_SANSSERIF_BOLD_FONT  "../res/freefont/FreeSansBold.ttf"
#define DEFAULT_SERIF_BOLD_FONT      "../res/freefont/FreeSerifBold.ttf"

TTF_Font* current_font;

void render_text(const char* text, int x, int y, int width, int height, SDL_Color color)
{
    if (current_font == NULL) {
        current_font = TTF_OpenFont(DEFAULT_MONOSPACE_FONT, 24);
    }

    TTF_SetFontSize(current_font, height);

    SDL_Surface* header_text = TTF_RenderText_Solid(current_font, text, color);
    if (header_text == NULL) {
	    log_error("Failed to render text: %s", TTF_GetError());
    }

    SDL_Texture* header_texture = SDL_CreateTextureFromSurface(window.renderer, header_text);

    SDL_Rect header_texture_rect;

    header_texture_rect.x = x;
    header_texture_rect.y = y;

    if (width < 0 || height < 0) { // automatic text size
        if (TTF_SizeText(current_font, text, &header_texture_rect.w, &header_texture_rect.h) < 0) {
            log_error("Error setting automatic text size: %s", TTF_GetError());
        }
    } else {
        header_texture_rect.w = width;
        header_texture_rect.h = height;
    }

    SDL_RenderCopy(window.renderer, header_texture, NULL, &header_texture_rect);

    // debug outline
    SDL_SetRenderDrawColor(window.renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(window.renderer, &header_texture_rect);

    // maalos: Do we do that now?
    SDL_FreeSurface(header_text);
    SDL_DestroyTexture(header_texture);
}

/**
 * @brief Loads a page
 *
 * @param url
 *        URL of page to load
 */
static void
load_page(const char *url)
{
    struct url url_info = parse_url(url);

    struct net_response res = resolve_url(url_info);
    if (res.status == RESPONSE_OK) {
        struct parse_node *tree =
            parse_html(res.pageData.dataPtr, res.pageData.data_len);

        // TODO: transition to browser view with tree
        handle_html(tree, url_info.host);
        free_html_tree(tree);
    } else if (res.status == RESPONSE_ERROR) {
        // TODO: transition to error screen
        log_error(
            "Failed to load page \"%s\" with error code %d", url, res.code);
    } else if (res.status == RESPONSE_HTTP_ERROR) {
        // TODO: transition to error screen
        log_error("Failed to load page \"%s\" with HTTP error code %d",
                  url,
                  res.code);
    } else if (res.status == RESPONSE_BUILTIN) {
        // TODO: open builtin page
    }

    free_url(&url_info);
}

/**
 * @brief Initializes the browser.
 *
 * @return True if the browser was initialized successfully;
 *         False otherwise.
 */
bool
browser_init()
{
    // suzwin_set_icon("../res/logo.png");

    load_page("http://info.cern.ch/hypertext/WWW/TheProject.html");
    return true;
}

/**
 * @brief Updated the browser. This function is called on every tick.
 *
 * @return True if the browser was updated successfully;
 *         False otherwise.
 */
bool
browser_update()
{
    ui_homepage_render(NULL);
    /*
        //make the whole screen grey
        SDL_SetRenderDrawColor(window.renderer, 0xDD, 0xDD, 0xDD, 0xFF);
        SDL_RenderClear(window.renderer);

        //add a dark grey bar at the top of the window
        SDL_Rect rect = (SDL_Rect){0, 0, window.width, window.height / 10};
        SDL_SetRenderDrawColor(window.renderer, 0x44, 0x44, 0x44, 0xFF);
        SDL_RenderFillRect(window.renderer, &rect);

        //add a darker grey bare half the height of the last one at the top
        rect = (SDL_Rect){0, 0, window.width, window.height / 20};
        SDL_SetRenderDrawColor(window.renderer, 0x22, 0x22, 0x22, 0xFF);
        SDL_RenderFillRect(window.renderer, &rect);

        SDL_Color color = { 200, 0, 0 };
    render_text("The Sovyetski Soyouzy Project",    0, 64,  -1, 64, color);
    render_text("GNU FreeMono 32px",                0, 128, -1, 32, color);
    render_text("GNU FreeMono 24px",                0, 160, -1, 24, color);
    render_text("GNU FreeMono 16px",                0, 192, -1, 16, color);
    render_text("GNU FreeMono 12px",                0, 216, -1, 12, color);

    */
    // suzwin_render_current_window();
    //  TODO: Update
    return true;
}

void
browser_destroy()
{
    // suzwin_destroy_all_windows();
    // suzwin_destroy_current_window();
}
