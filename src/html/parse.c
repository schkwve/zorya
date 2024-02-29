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
         log_debug(element_tag);
         break;
      }
      current_char++;
   }

   return element;
}

/**
 * @brief Parses HTML from raw text data
 * @param rawData The raw data to actually parse.
 * @param size The size of the data.
 * @return Returns an array of elements.
 */
element_t *parse_html(char *rawData, size_t size)
{
   char *current_line = rawData;
   element_t *elements = malloc(sizeof(element_t));
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

   element_t *elements = parse_html(rawData, size);
   free(elements);
   free(rawData);

   return 0;
}
