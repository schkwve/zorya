/**
 * @file parse.c
 * @brief Implementation of HTML (2.0) parser functions.
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 1/03/2024
 */

#include "parse.h"

char** _split_lines(char*  data);

element_t* parse_html(const char* data, size_t size) {
  element_t* element = malloc(sizeof(element_t));
  char* ptr = (char*)data;
 
  // TODO: Fix this stupid shit... aka add loop protection orwhatever. 
  while(1) {
    if(ptr > data + size) {
      break;
    }

    ptr = strtok(ptr, "<") + 1;
  
    if(ptr != NULL) {
      if(*(ptr + 1) == '/') {
        ptr = strtok(ptr, ">");
        
        if(ptr != NULL) {
          element->closing = true;
          log_debug("Found closing tag!");
        } else {
          element->closing = false;
          log_debug("Found opening tag!");
        }
      }
    }  
    
    char* tmp = strtok(ptr, " ");

    element->name = malloc(ptr - tmp);
    memcpy(element->name, ptr, ptr - tmp);
    ptr = strtok(ptr, ">");
    log_debug("%s", ptr);
  }
  
  return NULL;
}

