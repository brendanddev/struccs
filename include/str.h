// str.h
// Header for the string type implementation
// Brendan Dileo - 2026

#ifndef STR_H
#define STR_H

#include <stdbool.h>

// Starting capacity of a String's buffer, in characters (excluding the '\0').
#define INITIAL_CAPACITY 8

// Growable, always NUL-terminated string.
//   data     - heap buffer, capacity + 1 bytes (room for the '\0')
//   length   - characters stored, not counting the '\0'
//   capacity - characters the buffer can hold before it must grow
typedef struct String {
    char *data;
    size_t length;
    size_t initial_capacity;
    size_t capacity;
} String;

// Creates a String from a C string (or an empty String if initial is NULL).
// Caller frees it with str_discard. Returns NULL on allocation failure.
String* str_create(const char *initial);
// Appends the C string data in place, growing the buffer as needed. Returns false
// if a needed reallocation fails.
bool str_append(String *str, const char *data);
// Returns true if substr occurs in str (naive O(n*m) scan).
bool str_contains(String *str, const char *substr);
// Lexicographic compare: 0 if equal, +/-1 on an in-string mismatch, or the
// signed char delta when one string is a prefix of the other.
int str_compare(String *a, String *b);
// Returns true if a and b compare equal.
bool str_equals(String *a, String *b);
// Returns a newly allocated str followed by substr. Caller frees with str_discard.
String* str_concat(String *str, String *substr);
// Returns a newly allocated duplicate of src. Caller frees with str_discard.
String* str_copy(String *src);
// Returns a newly allocated upper-cased copy. Caller frees with str_discard.
String* str_to_upper(String *str);
// Returns a newly allocated lower-cased copy. Caller frees with str_discard.
String* str_to_lower(String *str);
// Returns a newly allocated copy with leading/trailing whitespace removed.
// Caller frees with str_discard.
String *str_trim(String *str);
// Returns the length of a raw C string (like strlen).
size_t str_length(const char *src);
// Returns str->length (no scan).
size_t str_len(String *str);
// Writes the String's characters to stdout.
void str_print(String *str);
// Frees the buffer and the String struct.
void str_discard(String *str);

#endif
