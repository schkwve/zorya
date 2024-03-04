/**
 * @file browser.c
 * @authors Kevin Alavik <kevin@alavik.se>
 *          lolguy91 <retek1544@gmail.com>
            maalos <maalos@pex.ovh>
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
#include <antiralsei/htmltree.h>
#include <netwerk/connect.h>
#include <netwerk/protocols/http.h>
#include <netwerk/resolver.h>
#include <netwerk/url.h>
#include <suzTK/window.h>
#include <utils/buffer.h>
#include <utils/host.h>
#include <utils/logging.h>
#include <core/user_agent.h>

#include <UI/home.h>

#define DEFAULT_MONOSPACE_FONT "../res/freefont/FreeMono.ttf"
#define DEFAULT_SANSSERIF_FONT "../res/freefont/FreeSans.ttf"
#define DEFAULT_SERIF_FONT "../res/freefont/FreeSerif.ttf"

#define DEFAULT_MONOSPACE_BOLD_FONT "../res/freefont/FreeMonoBold.ttf"
#define DEFAULT_SANSSERIF_BOLD_FONT "../res/freefont/FreeSansBold.ttf"
#define DEFAULT_SERIF_BOLD_FONT "../res/freefont/FreeSerifBold.ttf"

TTF_Font *current_font_monospace;
TTF_Font *current_font_sansserif;
TTF_Font *current_font_serif;

struct suztk_window *window;

// TODOS:
//  move HTML renderer into Antiralsei
//  move text component into SuzTK/Componyents
//  Hook up the statemachine
//  add some anti-aliasing

void
render_text(const char *text,
            int x,
            int y,
            int width,
            int height,
            SDL_Color color,
            TTF_Font *font)
{
    TTF_SetFontSize(font, height);

    SDL_Surface *header_text = TTF_RenderText_Solid(font, text, color);
    if (header_text == NULL) {
        log_error("Failed to render text: %s\nGiven parameters: %s, %d, %d, "
                  "%d, %d, ?color?",
                  TTF_GetError(),
                  text,
                  x,
                  y,
                  width,
                  height);
    }

    SDL_Texture *header_texture =
        SDL_CreateTextureFromSurface(window->renderer, header_text);

    SDL_Rect header_texture_rect;

    header_texture_rect.x = x;
    header_texture_rect.y = y;

    if (width < 0 || height < 0) { // automatic text size
        if (TTF_SizeText(
                font, text, &header_texture_rect.w, &header_texture_rect.h) <
            0) {
            log_error("Error setting automatic text size: %s", TTF_GetError());
        }
    } else {
        header_texture_rect.w = width;
        header_texture_rect.h = height;
    }

    SDL_RenderCopy(
        window->renderer, header_texture, NULL, &header_texture_rect);

    // debug outline
    SDL_SetRenderDrawColor(window->renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(window->renderer, &header_texture_rect);

    // maalos: Do we do that now?
    SDL_FreeSurface(header_text);
    SDL_DestroyTexture(header_texture);
}

static const char *
get_element_content(struct parse_element *element)
{
    if (element != NULL && element->content != NULL) {
        return element->content;
    }

    return NULL;
}

typedef struct
{
    char *text;
    int x;
    int y;
    int width;
    int height;
    SDL_Color color;
    TTF_Font *font;
} render_node;

render_node render_array[64];

static void
render_element(struct parse_element *element)
{
    const char *element_content = get_element_content(element);
    int element_content_length = strlen(element_content) + 1;

    SDL_Color foreground_color = { 0, 0, 0 };
    // TODO: implement parse_attribute based color setting

    render_array[1].text = malloc(sizeof(char) * element_content_length);
    snprintf(render_array[1].text, element_content_length, element_content);
    render_array[1].x = 0;
    render_array[1].y = 72;
    render_array[1].width = -1;
    render_array[1].height = 37;
    render_array[1].color = foreground_color;
    render_array[1].font = current_font_sansserif;
}

static void
render_html(struct parse_node *tree)
{
    log_debug("Rendering HTML content");

    if (tree == NULL) {
        log_error("Tried rendering empty HTML tree!");
        return;
    }

    struct parse_element *element = find_in_html_tree(tree, "h1");

    render_element(element);
}

static void
render_url(const char *url)
{
    SDL_Color foreground_color = { 255, 255, 255 };

    int url_length = strlen(url);

    render_array[0].text = malloc(sizeof(char) * (url_length + 1));
    snprintf(render_array[0].text, url_length, url);
    render_array[0].x = 8;
    render_array[0].y = window->height / 13 - 8;
    render_array[0].width = -1;
    render_array[0].height = 16;
    render_array[0].color = foreground_color;
    render_array[0].font = current_font_monospace;
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
        render_html(tree);
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

    render_url(url);

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
    current_font_monospace = TTF_OpenFont(DEFAULT_MONOSPACE_FONT, 32);
    current_font_sansserif = TTF_OpenFont(DEFAULT_SANSSERIF_FONT, 32);
    current_font_serif = TTF_OpenFont(DEFAULT_SERIF_FONT, 32);

    user_agent_infer();

    window = suzwin_create_window(1280, 720, 0, "");
    suzwin_set_icon(window, "../res/logo.png");

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
    // ui_homepage_render(NULL);

    // make the whole screen grey
    SDL_SetRenderDrawColor(window->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(window->renderer);

    SDL_Rect rect = (SDL_Rect){ 0, 0, window->width, window->height / 10 };
    SDL_SetRenderDrawColor(window->renderer, 0x44, 0x44, 0x44, 0xFF);
    SDL_RenderFillRect(window->renderer, &rect);

    rect = (SDL_Rect){ 0, 0, window->width, window->height / 20 };
    SDL_SetRenderDrawColor(window->renderer, 0x22, 0x22, 0x22, 0xFF);
    SDL_RenderFillRect(window->renderer, &rect);

    // SDL_Color color = { 200, 0, 0 };
    //  render_text("The Sovyetski Soyouzy Project", 0, 64, -1, 64, color);
    //  render_text("GNU FreeMono 32px", 0, 128, -1, 32, color);
    //  render_text("GNU FreeMono 24px", 0, 160, -1, 24, color);
    //  render_text("GNU FreeMono 16px", 0, 192, -1, 16, color);
    //  render_text("GNU FreeMono 12px", 0, 216, -1, 12, color);

    for (int i = 0; i < 64; i++) {
        if (render_array[i].text == NULL)
            continue;
        render_text(render_array[i].text,
                    render_array[i].x,
                    render_array[i].y,
                    render_array[i].width,
                    render_array[i].height,
                    render_array[i].color,
                    render_array[i].font);
    }

    suzwin_render_window(window);
    //  TODO: Update
    return true;
}

void
browser_destroy()
{
    suzwin_destroy_window(window);
}
