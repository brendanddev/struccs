// str.h
// Header for the string type implementation
// Brendan Dileo - 2026

#ifndef STR_H
#define STR_H

#include <stdbool.h>

#define INITIAL_CAPACITY 8

// Defines the String struct type
// `data` is a pointer to where the buffer is stored in memory
// `length` is the number of characters currently stored (excluding '\0')
// `initial_capacity` is the starting number of characters the buffer can store
// `capacity` is the current number of characters the buffer can store
typedef struct String {
    char *data;
    size_t length;
    size_t initial_capacity;
    size_t capacity;
} String;

String* str_create(const char *initial);
bool str_append(String *str, const char *data);
bool str_contains(String *str, const char *substr);
int str_compare(String *a, String *b);
bool str_equals(String *a, String *b);
String* str_concat(String *str, String *substr);
String* str_copy(String *src);
String* str_to_upper(String *str);
String* str_to_lower(String *str);
String *str_trim(String *str);
size_t str_length(const char *src);
size_t str_len(String *str);
void str_print(String *str);
void str_discard(String *str);

#endif
