# Coding Guidelines

---

## General

- Use 4 spaces per indentation level.
- Always check for invalid input at the beginning of a function.
- Pointers are always aligned to the right.

## Naming

- All names must be `snake_case`, lowercase only.
- Functions' names should be kept short and descriptive.
- Functions' names should be prefixed with their module name (ie. `net_create_connection()` belongs to the networking module). This does not apply to private functions.
- Global variables that are exported in a header file should be prefixed with `g_`.
- Macros should always be named in all-uppercase `SNAKE_CASE`.
- Any amount of underscores shouldn't be used as a prefix or a suffix to a name (ie. `__function()`). Underscores are usually reserved for compilers.
- File names should be all lowercase, preferably a single word.
- Treat all filenames as case-insensitive (ie. `this.c` and `This.c` should **NEVER** occur inside the same directory).

 ## Functions

 - Functions should be as short as possible.
 - Functions that are used only in a single source file should be defined at the beginning of the source file and should have the `static` modifier.
 - Functions that are used in multiple files, but should not be used outside of their module should have `priv` after the module's name (ie. `net_priv_connect_socket()`), and should be defined at the bottom of the source file.

 ## Structures & Variables

 - Use proper types when declaring variables (ie. Don't use `uint32_t` for holding a return value of `sizeof()`).
 - Structures, enumerations and other data types should **never** have a `_t` suffix. This suffix is reserved by C.
 - Data structures however are allowed to be typedef'd with a `_t` suffix (ie. Linked lists, buffers binary trees, ...).

 ## Files

 - All source files are required to include this header at the beginning:

```c
/**
 * @file path/to/file.c
 * @author John Doe <john.doe@example.com>
 * @date 01/01/1970
 * @brief Short description about what this file implements
 */
```
> [!NOTE]  
> Date follows the DD/MM/YYYY format.

- Header files should always have an include guard after the header like this:

```c
#ifndef MODULE_FILENAME_H
#define MODULE_FILENAME_H

...

#endif /* MODULE_FILENAME_H */
```

## Documentation

- All functions, structures, global variables etc. should have a Doxygen-compatible documentation:

```c
/**
 * @brief Creates a new connection entry and connects to a remote server.
 *
 * @param host
 *        Stripped URL string (only hostname/IP address
 *        should be present). Ex: www.website.com OR 127.0.0.1
 *
 * @param port
 *        Which port to connect to
 *
 * @return New connection structure if it was created successfully;
 *         NULL otherwise.
 */
struct net_connection *net_create_connection(char *host, uint16_t port)
{
    /* ... */
}
```

- You can omit the `@param` command if there are no parameters. The same applies for `@return`.
- If a parameter is allowed to not be specified (ie. `0` or `NULL`), make sure to put `[optional]` after the parameter name:

```c
 * @param is_fullscreen [optional]
```
