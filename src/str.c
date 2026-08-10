// str.c
// Implementation of a string
// Brendan Dileo - 2026

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "str.h"

// Prototypes
static bool resize(String *str, size_t size);
static bool is_whitespace(char c);

// Creates a new String
String* str_create(const char *initial) {
    String *str = malloc(sizeof(String));
    if (str == NULL) return NULL;

    str->initial_capacity = INITIAL_CAPACITY;
    str->capacity = INITIAL_CAPACITY;

    if (initial == NULL) {
        str->data = malloc(sizeof(char) * (str->initial_capacity + 1));
        if (str->data == NULL) {
            free(str);
            return NULL;
        }

        // Dereference to set the first character stored in the buffer to null terminator
        *str->data = '\0';
        str->length = 0;

    } else {
        size_t length = str_length(initial);

        str->data = malloc(sizeof(char) * (str->initial_capacity + 1));
        if (str->data == NULL) {
            free(str);
            return NULL;
        }

        if (resize(str, length)) {
            memcpy(str->data, initial, length + 1); 
            str->length = length;
        } else {
            free(str);
            return NULL;
        }
    }

    return str;
}

// Adds more characters to the end of an existing String
bool str_append(String *str, const char *data) {
    size_t append_length = str_length(data);
    size_t new_length = str->length + append_length;

    if (resize(str, new_length)) {
        char *buffer_end = str->data + str->length;
        memcpy(buffer_end, data, append_length + 1);
        str->length = new_length;
        return true;
    } else {
        return false;
    }
}

// Checks if a string contains a given substring
bool str_contains(String *str, const char *substr) { 
    char *curr_str = str->data;
    char *curr_substr = substr;

    while (*curr_str != '\0' && *curr_substr != '\0') {
        curr_substr = substr;
        while (*curr_str == *curr_substr) {
            curr_str++;
            curr_substr++;
            if (*curr_substr == '\0') {
                return true;
            }
        }
        curr_str++;
    }
    return false;
}

// Compares two strings lexicographically
// Returns 0 if equal, 1 if a > b, -1 if a < b, 
// or the character difference if lengths differ
int str_compare(String *a, String *b) {
    char *curr_a = a->data;
    char *curr_b = b->data;

    while (*curr_a != '\0' && *curr_b != '\0') {
        if (*curr_a > *curr_b) {
            return 1;
        } else if (*curr_a < *curr_b) {
            return -1;
        } else {
            curr_a++;
            curr_b++;
        }
    }
    // return 0;
    return *curr_a - *curr_b;
}

// Returns a copy of the provided string
String* str_copy(String *src) {
    if (src == NULL) return NULL;
    String *new_str = str_create(src->data);
    return new_str;
}

// Checks if two strings are equal
bool str_equals(String *a, String *b) {
    return str_compare(a, b) == 0;
}

// Concatenates two strings, and returns a copy
String* str_concat(String *str, String *substr) {
    if (str == NULL) {
        return NULL;
    }
    String *concat_str = str_create(str->data);
    if (str_append(concat_str, substr->data)) {
        return concat_str;
    } else {
        str_discard(concat_str);
        return NULL;
    }
}

// Converts a string to uppercase, and returns a copy of that string
String* str_to_upper(String *str) {
    if (str == NULL) {
        return NULL;
    }

    String *str_upper = str_create(str->data);
    char *current = str_upper->data;
    while (*current != '\0') {
        if (*current >= 'a' && *current <= 'z') {
            *current = *current - 32;
        }
        current++;
    }
    return str_upper;
}

// Converts a string to lowercase, and returns a copy of that string
String* str_to_lower(String *str) {
    if (str == NULL) {
        return NULL;
    }

    String *str_lower = str_create(str->data);
    char *current = str_lower->data;
    while (*current != '\0') {
        if (*current >= 'A' && *current <= 'Z') {
            *current = *current + 32;
        }
        current++;
    }
    return str_lower;
}

// Trims whitespace from the start and end of a string, returns a copy
String *str_trim(String *str) {
    if (str == NULL) {
        return NULL;
    }

    char *start = str->data;
    char *end = str->data + str_len(str) - 1;

    while (is_whitespace(*start) && *start != '\0') {
        start++;
    }

    while (is_whitespace(*end) && end > start) {
        end--;
    }

    char *tempbuff = malloc(end - start + 2);
    if (tempbuff == NULL) {
        return NULL;
    }
    memcpy(tempbuff, start, end - start + 1);
    tempbuff[end - start + 1] = '\0';
    
    String *trimmed_str = str_create(tempbuff);
    free(tempbuff);
    return trimmed_str;
}

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

// Returns the length of string based on length member
size_t str_len(String *str) {
    return str->length;
}

// Prints the contents of the String
void str_print(String *str) {
    char *current = str->data;
    while (*current != '\0') {
        printf("%c", *current);
        current++;
    }
}

// Releases the String buffer and the String struct memory
void str_discard(String *str) {
    if (str != NULL) {
        free(str->data);
        free(str);
    }
}

// Ensures the internal buffer has enough capacity for the requested number of characters
static bool resize(String *str, size_t size) {
    if (size <= str->capacity) {
        return true;
    }

    size_t new_capacity = str->capacity * 2;
    while (size > new_capacity) {
        new_capacity = new_capacity * 2;
    }

    char *tmp = realloc(str->data, (new_capacity + 1) * sizeof(char));
    if (tmp == NULL) {
        return false;
    }

    str->capacity = new_capacity;
    str->data = tmp;
    return true;
}

// Returns true if char is whitespace, otherwise false
static bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}
