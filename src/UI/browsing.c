/**
 * @file UI/browsing.c
 * @author lolguy91 <retek1544@gmail.com>
 * @date 01/03/24
 * @brief Homepage
 */

#include <assert.h>
#include <stdlib.h>
#include "browsing.h"
#include <antiralsei/handler.h>
#include <suzTK/window.h>
#include <utils/string.h>
#include <SDL.h>
#include <SDL_ttf.h>

// TODOS:
//  move HTML renderer into Antiralsei
//  move text component into SuzTK/Componyents
//  add some anti-aliasing to the text

// this solution is bad, but it works
// should we pass the window around or have the current window be in the window manager?
extern struct suztk_window *window;

#define DEFAULT_MONOSPACE_FONT "../res/freefont/FreeMono.ttf"
#define DEFAULT_SANSSERIF_FONT "../res/freefont/FreeSans.ttf"
#define DEFAULT_SERIF_FONT "../res/freefont/FreeSerif.ttf"

#define DEFAULT_MONOSPACE_BOLD_FONT "../res/freefont/FreeMonoBold.ttf"
#define DEFAULT_SANSSERIF_BOLD_FONT "../res/freefont/FreeSansBold.ttf"
#define DEFAULT_SERIF_BOLD_FONT "../res/freefont/FreeSerifBold.ttf"

TTF_Font *current_font_monospace;
TTF_Font *current_font_sansserif;
TTF_Font *current_font_serif;

struct ui_browsing_args *args;

void render_text(const char *text,
                 int x,
                 int y,
                 int width,
                 int height,
                 SDL_Color color,
                 TTF_Font *font)
{
    TTF_SetFontSize(font, height);

    SDL_Surface *header_text = TTF_RenderText_Blended(font, text, color);
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

    // maalos: Do we do that now?
    SDL_FreeSurface(header_text);
    SDL_DestroyTexture(header_texture);
}

static const char *get_element_content(struct parse_element *element)
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

int curI = 1;
int curY = 72;
static void render_element(struct parse_element *element)
{
    assert(element != NULL);
    char* lowername = str_tolower(element->name);
    //TODO: represent these as css args or smth
    int text_size = 20;
    int text_margin = 8;

    if(strcmp(lowername, "h1") == 0) {
        text_size = 32;
    }else if (strcmp(lowername, "h2") == 0) {
        text_size = 24;
    }else if (strcmp(lowername, "h3") == 0) {
        text_size = 20;
    }else if (strcmp(lowername, "h4") == 0) {
        text_size = 18;
    }else if (strcmp(lowername, "h5") == 0) {
        text_size = 16;
    }else if (strcmp(lowername, "h6") == 0) {
        text_size = 14;
    }else if (strcmp(lowername, "p") == 0) {
        text_margin = 16;
    }

    const char *element_content = get_element_content(element);
    if (element_content == NULL) {
        goto cleanup;
    }
    int element_content_length = strlen(element_content) + 1;
    SDL_Color foreground_color = { 0, 0, 0 };
    render_array[curI].text = malloc(sizeof(char) * element_content_length);
    snprintf(render_array[curI].text,
             element_content_length,
             "%s",
             element_content);
    render_array[curI].x = 0;
    render_array[curI].y = curY;
    render_array[curI].width = -1;
    render_array[curI].height = text_size;
    render_array[curI].color = foreground_color;
    render_array[curI].font = current_font_sansserif;
    log_debug("Rendered an \"%s\". Content: \"%s\"",
              element->name,
              element->content);
    curI++;
    curY += text_size + 4;

    cleanup:
        free(lowername);
}

static void render_all_elements_from_tree(struct parse_node *tree)
{
    if (tree == NULL) {
        log_error("Tried rendering empty HTML tree!");
        return;
    }

    if (tree->element != NULL) {
        render_element(tree->element);
    }

    for (int i = 0; i < tree->num_children && tree->children != NULL; i++) {
        render_all_elements_from_tree(tree->children[i]);
    }
}

static void render_html(struct parse_node *tree)
{
    log_debug("Rendering HTML content");
    struct parse_node *body = find_in_html_tree(tree, "body");
    render_all_elements_from_tree(body);
}

static void render_url(const char *url)
{
    SDL_Color foreground_color = { 255, 255, 255 };

    int url_length = strlen(url) + 1;

    render_array[0].text = malloc(sizeof(char) * url_length + 1);
    snprintf(render_array[0].text, url_length + 1, "%s", url);
    render_array[0].x = 8;
    render_array[0].y = window->height / 13 - 8;
    render_array[0].width = -1;
    render_array[0].height = 16;
    render_array[0].color = foreground_color;
    render_array[0].font = current_font_monospace;
}


/**
 * @brief Initializes browsing Page
 *
 */
void ui_browsing_init(void* import_data)
{
    assert(import_data != NULL);
    args = (struct parse_node*)import_data;

    // TODO: asset manager
    current_font_monospace = TTF_OpenFont(DEFAULT_MONOSPACE_FONT, 32);
    current_font_sansserif = TTF_OpenFont(DEFAULT_SANSSERIF_FONT, 32);
    current_font_serif = TTF_OpenFont(DEFAULT_SERIF_FONT, 32);

    handle_html(args->tree, args->url->host);// TODO: ge the URL for fallback
    render_html(args->tree);
    render_url(args->url->host);
}

/**
 * @brief Renders browsing Page
 *
 */
void ui_browsing_render() {
    // make the whole screen grey
    SDL_SetRenderDrawColor(window->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(window->renderer);

    SDL_Rect rect = (SDL_Rect){ 0, 0, window->width, window->height / 10 };
    SDL_SetRenderDrawColor(window->renderer, 0x44, 0x44, 0x44, 0xFF);
    SDL_RenderFillRect(window->renderer, &rect);

    rect = (SDL_Rect){ 0, 0, window->width, window->height / 20 };
    SDL_SetRenderDrawColor(window->renderer, 0x22, 0x22, 0x22, 0xFF);
    SDL_RenderFillRect(window->renderer, &rect);

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
}

/**
 * @brief Destroys browsing Page
 *
 */
void ui_browsing_destroy() {
    free_url(args->url);
    free(args->url);
    free_html_tree(args->tree);
    for (int i = 0; i < 64; i++) {
        if (render_array[i].text == NULL)
            continue;
        free(render_array[i].text);
    }
    TTF_CloseFont(current_font_monospace);
    TTF_CloseFont(current_font_sansserif);
    TTF_CloseFont(current_font_serif);
    free(args);
}
