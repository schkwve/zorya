/**
 * @file browser.c
 * @authors Kevin Alavik <kevin@alavik.se>
 *          lolguy91 <retek1544@gmail.com>
 * @date 02/03/2024
 * @brief Source file for core/browser.h
 */

#include <SDL.h>
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
        //make the whole screen red
        SDL_SetRenderDrawColor(window.renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderClear(window.renderer);

        //add a green bar at the top of the window
        SDL_Rect rect = (SDL_Rect){0, 0, window.width, window.height / 10};
        SDL_SetRenderDrawColor(window.renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderFillRect(window.renderer, &rect);

        //add a blue bare half the height of the last one at the top
        rect = (SDL_Rect){0, 0, window.width, window.height / 20};
        SDL_SetRenderDrawColor(window.renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderFillRect(window.renderer, &rect);

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
