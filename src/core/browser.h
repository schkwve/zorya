/**
 * @file browser.h
 * @brief Imepelementation for the browser part of the core
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 2/03/2024
 */

#ifndef __BROWSER_H__
#define __BROWSER_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool browserInit();
bool browserUpdate();
bool browserDestroy();

#endif // __BROWSER_H__
