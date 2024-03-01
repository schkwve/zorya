#include "../src/html/parse.h"
#include "../src/utils/logging.h"
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        log_info("Usage: %s filename", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        log_error("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* data = (char*)malloc(file_size + 1);
    if (data == NULL) {
        log_fatal("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(data, 1, file_size, file);
    if (bytes_read != file_size) {
        log_error("Error reading file");
        fclose(file);
        free(data);
        return EXIT_FAILURE;
    }
    data[file_size] = '\0';

    fclose(file);

    element_t* elements = parse_html(data, strlen(data));

    free(data);

    return EXIT_SUCCESS;
}
