/**
 * @file html/parse.c
 * @author Kevin Alavik <kevin@alavik.se>
 * @date 29/02/2024
 * @brief Entry point for HTML (2.0) parser, see .h
 */

#include "parse.h"

/**
 * @brief A private function to parse an element from a line, called from parse_html
 * @param line The line to parse
 * @return Returns the parsed element
 */
element_t _parse_element(char *line)
{
  element_t element;
  memset(&element, 0, sizeof(element_t));

  char *current_char = line;
  char element_tag[100];
  int index = 0;

  while (*current_char != '\0')
  {
    if (*current_char == '<')
    {
      current_char++;
      while (*current_char != '\0' && *current_char != ' ' && *current_char != '>')
      {
        element_tag[index++] = *current_char;
        current_char++;
      }
      element_tag[index] = '\0';
      log_debug("Found tag: %s", element_tag);
      if(element_tag[0] == '/') {
        log_debug("%s is a closing tag!", element_tag);
        element.type = CLOSING_ELEMENT;
      } else {
        if(strcmp(element_tag, "!DOCTYPE") == 0) {
         log_debug("%s is a document type decleration tag!", element_tag);
         element.type = DTD_ELEMENT;
        }
      }
      break;
    }
    current_char++;
  }

  element.tag = strdup(element_tag);

  return element;
}

/**
 * @brief Parses HTML from raw text data
 * @param rawData The raw data to actually parse.
 * @return Returns an array of elements.
 */
element_t *parse_html(char *rawData)
{
  char *current_line = rawData;
  element_t *elements = NULL;
  size_t num_elements = 0;

  while (*rawData != '\0')
  {
    if (*rawData == '\n')
    {
      *rawData = '\0';
      element_t new_element = _parse_element(current_line);
      elements = realloc(elements, (num_elements + 1) * sizeof(element_t));
      elements[num_elements] = new_element;
      num_elements++;
      current_line = rawData + 1;
    }
    rawData++;
  }

  if (current_line != rawData)
  {
    element_t new_element = _parse_element(current_line);
    elements = realloc(elements, (num_elements + 1) * sizeof(element_t));
    elements[num_elements] = new_element;
    num_elements++;
  }

  return elements;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *rawData = malloc(size + 1);
  if (rawData == NULL)
  {
    fclose(file);
    perror("Memory allocation failed");
    return 1;
  }

  if (fread(rawData, 1, size, file) != size)
  {
    fclose(file);
    free(rawData);
    perror("Error reading file");
    return 1;
  }

  rawData[size] = '\0';

  fclose(file);

  log_info("Parsing %s", argv[1]);
  element_t *elements = parse_html(rawData);

  size_t elementCount = 0;
  element_t *temp = elements;
  while (temp != NULL && temp[elementCount].tag != NULL) {
    elementCount++;
  }

  for (size_t i = 0; i < elementCount; i++) {
    log_info("Parsed element %s", elements[i].tag);
    free(elements[i].tag);
  }

  free(elements);
  free(rawData);

  return 0;
}
