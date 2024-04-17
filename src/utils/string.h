#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)

char *str_tolower(char *str);

#endif /* UTILS_STRING_H */
