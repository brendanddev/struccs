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

bool str_contains(const String *str, const char *substr) {
    const char *curr_str = str->data;
    const char *curr_substr = substr;
    const char *match_start = NULL;

    // Naive search: retry the match one character further along str after every
    // failed attempt.
    while (*curr_str != '\0' && *curr_substr != '\0') {
        curr_substr = substr;
        match_start = curr_str + 1;
        while (*curr_str == *curr_substr) {
            curr_str++;
            curr_substr++;
            if (*curr_substr == '\0') {
                return true;
            }
        }
        curr_str = match_start;
    }
    return false;
}

int str_compare(const String *a, const String *b) {
    const char *curr_a = a->data;
    const char *curr_b = b->data;

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
    // Loop ended because a string ran out: 0 if both did, else the signed value
    // of the leftover character (not necessarily +/-1).
    return *curr_a - *curr_b;
}

String* str_copy(const String *src) {
    if (src == NULL) return NULL;
    String *new_str = str_create(src->data);
    return new_str;
}

bool str_equals(const String *a, const String *b) {
    return str_compare(a, b) == 0;
}

String* str_concat(const String *str, const String *substr) {
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

String* str_to_upper(const String *str) {
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

String* str_to_lower(const String *str) {
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

String *str_trim(const String *str) {
    if (str == NULL) {
        return NULL;
    }

    const char *start = str->data;
    // NOTE: assumes str is non-empty. For a zero-length String this is data - 1,
    // and the trailing-whitespace loop below then reads before the buffer.
    const char *end = str->data + str_len(str) - 1;

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

size_t str_length(const char *src) {
    const char *current = src;
    size_t length = 0;

    while (*current != '\0') {
        current++;
        length++;
    }
    return length;
}

size_t str_len(const String *str) {
    return str->length;
}

void str_print(const String *str) {
    const char *current = str->data;
    while (*current != '\0') {
        printf("%c", *current);
        current++;
    }
}

void str_discard(String *str) {
    if (str != NULL) {
        free(str->data);
        free(str);
    }
}

// Grows data so it can hold at least `size` characters plus the '\0', doubling
// capacity until it fits. No-op when the buffer already fits; false if realloc fails.
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

static bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}
