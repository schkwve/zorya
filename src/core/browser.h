/**
 * @file browser.h
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 02/03/2024
 * @brief Imepelementation for the browser part of the core
 */

#ifndef BROWSER_H
#define BROWSER_H

#include <stdbool.h>

bool
browser_init();

bool
browser_update();

void
browser_destroy();

#endif /* BROWSER_H */
