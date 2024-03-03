/**
 * @file UI/error.h
 * @author lolguy91 <retek1544@gmail.com>
 * @date 01/03/24
 * @brief ErrorPage
 */

#ifndef UI_ERROR_H
#define UI_ERROR_H

#include <stdio.h>

/*
    @brief Initialize Home Page
*/
void* initErrorPage();

/*
    @brief Render Home Page
*/
void renderErrorPage(void* PP);
/* 
    @brief Destroy Home Page
*/
void destroyErrorPage(void* PP);

#endif
