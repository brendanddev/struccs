// str.c
// Implementation of a string
// Brendan Dileo - 2026

#include <string.h>
#include <stdlib.h>
#include "str.h"


String* str_create(const char *initial) {
    String *str = malloc(sizeof(String));
    if (str == NULL) return NULL;

    str->initial_capacity = INITIAL_CAPACITY;
    str->capacity = INITIAL_CAPACITY;

    if (initial == NULL) {
        str->data = malloc(sizeof(char) * str->initial_capacity);
        if (str->data == NULL) {
            free(str);
            return NULL;
        }

        // Dereference to set the first character stored in the buffer to null terminator
        *str->data = '\0';
        str->length = 0;

    } else {
        size_t length = str_length(initial);
        resize(str, length);


    }

    return str;
}

//     // Otherwsie need to copy the string passed in, going to the address of where the string points to,
//     // and copy it over using memcpy
//     } else {
//         char *current = initial;
//         int num = 0;
//         while (*current != '\0') {
//             current++;
//             num++;
//         }

//         // If the size of the string passed in is larger than initial capacity,
//         // need to resize
//         if (num + 1 > INITIAL_CAPACITY) {
//             resize(str);
//             memcpy(str->data, initial, num + 1);            

//         // Otherwise just copy in
//         } else {
//             memcpy(str->data, initial, num + 1);            
//         }
//     }

//     return str;
// }




// Returns the length of the string
size_t str_length(const char *src) {
    const char *current = src;
    size_t length = 0;

    while (*current != '\0') {
        current++;
        length++;
    }

    return length;
}


// bool str_append(String *str, const char *data);
// bool str_contains(String *str, const char *substr);
// int str_compare(String *a, String *b);
// String* str_copy(String *src);
// int str_length(String *src);
// void str_print(String *str);
// void str_discard(String *str);


// Resizes the internal buffer when capacity is reached
static void resize(String *str, size_t size) {
    size_t new_capacity = str->capacity * 2;
    
    while (size > new_capacity) {
        new_capacity = new_capacity * 2;
    }

    char *tmp = realloc(str->data, (new_capacity + 1) * sizeof(char));

    str->capacity = new_capacity;
    str->data = tmp;
}
