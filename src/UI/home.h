/**
 * @file UI/home.h
 * @author lolguy91 <retek1544@gmail.com>
 * @date 01/03/24
 * @brief Homepage
 */

#ifndef PAGES_H
#define PAGES_H

#include <stdio.h>

/*
    @brief Initialize Home Page
*/
void* initHomePage();

/*
    @brief Render Home Page
*/
void renderHomePage(void* PP);
/* 
    @brief Destroy Home Page
*/
void destroyHomePage(void* PP);

#endif
