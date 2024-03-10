/**
 * @file UI/browsing.h
 * @author lolguy91 <retek1544@gmail.com>
 * @date 01/03/24
 * @brief Homepage
 */

#ifndef UI_HOME_H
#define UI_HOME_H
#include <antiralsei/htmltree.h>
#include <netwerk/url.h>

struct ui_browsing_args {
    struct parse_node *tree;
    struct url *url;
};

void ui_browsing_init(void* import_data);

void ui_browsing_render();

void ui_browsing_destroy();

#endif
