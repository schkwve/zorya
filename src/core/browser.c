/**
 * @file browser.c
 * @brief Source file for core/browser.h
 * @author Kevin Alavik <kevin@alavik.se> lolguy91 <retek1544@gmail.com>
 * @date 2/03/2024
 */
#include "browser.h"

#include <antiralsei/parse.h>
#include <antiralsei/handler.h>
#include <netwerk/connect.h>
#include <netwerk/protocols/http.h>
#include <netwerk/url.h>
#include <netwerk/resolver.h>
#include <utils/logging.h>
#include <utils/buffer.h>
#include <utils/host.h>
#include <SDL.h>
#include <suzTK/window.h>
#include <main.h>

void loadPage(const char* url);

bool browserInit()
{
    suzwin_set_icon("../res/logo.png");

    loadPage("http://info.cern.ch/hypertext/WWW/TheProject.html");
    return true;
}
bool browserUpdate()
{
    //renderHomePage();

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


    suzwin_render_current_window();
    // TODO: Update
    return true;
}
bool
browserDestroy()
{
    //suzwin_destroy_all_windows();
    suzwin_destroy_current_window();
    return true;
}

void loadPage(const char* url){

    Url urlInfo = parseUrl(url);

    response_t res = resolveUrl(urlInfo);
    if(res.status == RESPONSE_OK){
        node_t* tree = parse_html(res.pageData.dataPtr, res.pageData.dataLen);
        
        //TODO: transition to browser view with tree
        handle_html(tree,urlInfo.host);
        free_html_tree(tree);
    }else if(res.status == RESPONSE_ERROR){
        //TODO: transition to error screen
        log_error("Failed to load page \"%s\" with error code %d", url, res.code);
    }else if(res.status == RESPONSE_HTTP_ERROR){
        //TODO: transition to error screen
        log_error("Failed to load page \"%s\" with HTTP error code %d", url, res.code);
    }else if(res.status == RESPONSE_BUILTIN){
        //TODO: open builtin page
    }
    freeUrl(&urlInfo);
}