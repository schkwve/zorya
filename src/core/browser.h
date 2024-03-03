/**
 * @file browser.h
 * @brief Imepelementation for the browser part of the core
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 2/03/2024
 */

#ifndef __BROWSER_H__
#define __BROWSER_H__

#include "../main.h"
#include "../html/parse.h"
#include "../html/handler.h"
#include "../netwerk/connect.h"
#include "../netwerk/http.h"
#include "../utils/logging.h"
#include "../utils/buffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void render_page(const char* url);

#endif // __BROWSER_H__
