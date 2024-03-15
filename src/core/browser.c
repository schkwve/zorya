/**
 * @file browser.c
 * @authors Kevin Alavik <kevin@alavik.se>
 *          lolguy91 <retek1544@gmail.com>
            maalos <maalos@pex.ovh>
 * @date 02/03/2024
 * @brief Source file for core/browser.h
 */

#include <SDL.h>

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "browser.h"
#include "config.h"
#include <antiralsei/htmltree.h>
#include <core/user_agent.h>
#include <netwerk/protocols/http.h>
#include <netwerk/resolver.h>
#include <netwerk/url.h>
#include <suzTK/window.h>
#include <utils/buffer.h>
#include <utils/host.h>
#include <utils/logging.h>

#include <UI/statemachine.h>
#include <UI/browsing.h>

struct suztk_window *window;


/**
 * @brief Loads a page
 *
 * @param url
 *        URL of page to load
 */
static void load_page(const char *url)
{

    struct url *url_info = malloc(sizeof(struct url));
    *url_info = parse_url(url);

    struct net_response res = resolve_url(*url_info);
    if (res.status == RESPONSE_OK) {
        struct parse_node *tree =
            parse_html(res.page_data.data_ptr, res.page_data.data_len);

        struct ui_browsing_args *args = malloc(sizeof(struct ui_browsing_args));
        args->tree = tree;
        args->url = url_info;

        ui_statemachine_goto_page("browsing",(void*)args);
        if (res.raw_response_type == RAW_RESPONSE_TYPE_HTTP) {
            // clarification: derefencing the raw response as an http_response struct
            free_http_response(*((struct http_response*)res.raw_response));
            free(res.raw_response);
        }
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
}

/**
 * @brief Initializes the browser.
 *
 * @return True if the browser was initialized successfully;
 *         False otherwise.
 */
bool browser_init()
{
    // OpenSSL can shit itself if SIGPIPE isn't ignored
    signal(SIGPIPE, SIG_IGN);

    log_debug("Browser identifies as \"%s %s(%s)\"",
        BROWSER_NAME, 
        BROWSER_VERSION_STRING, 
        BROWSER_VERSION_CODENAME);

    user_agent_infer();
    log_debug("User agent: %s", g_user_agent);

    window = suzwin_create_window(1280, 720, 0, "LOL SUS BROWSER"); // easter egg ;)
    suzwin_set_icon(window, "../res/logo.png");

    load_page("https://kevinalavik.github.io/html-2.0-test/");
    return true;
}

/**
 * @brief Updated the browser. This function is called on every tick.
 *
 * @return True if the browser was updated successfully;
 *         False otherwise.
 */
bool browser_update()
{
    ui_statemachine_render_current_page();

    suzwin_render_window(window);
    return true;
}

void browser_destroy()
{
    ui_statemachine_destroy_current_page();
    suzwin_destroy_window(window);
}
