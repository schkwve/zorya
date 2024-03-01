/**
 * @file parse.c
 * @brief Implementation of HTML (2.0) parser functions.
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 1/03/2024
 */

#include "parse.h"

char** _split_lines(char*  data);

element_t* parse_html(const char* data) {
  char* raw = (char*)data;
  
  char** lines = _split_lines(raw); 
  for (int i = 0; lines[i] != NULL; i++) {
    log_debug("%s", lines[i]);
  }

  return NULL;
}


char** _split_lines(char* data)
{
    char** lines = NULL;
    int num_lines = 0;
    char* line = strtok(data, "\n");
    while (line != NULL) {
        lines = realloc(lines, (num_lines + 1) * sizeof(char*));
        if (lines == NULL) {
            log_fatal("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        char* non_space_ptr = line;
        while (*non_space_ptr == ' ') {
            non_space_ptr++;
        }

        lines[num_lines] = strdup(non_space_ptr);
        if (lines[num_lines] == NULL) {
            log_fatal("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        num_lines++;
        line = strtok(NULL, "\n");
    }

    lines = realloc(lines, (num_lines + 1) * sizeof(char*));
    if (lines == NULL) {
        log_fatal("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    lines[num_lines] = NULL;
    return lines;
}
