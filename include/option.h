// option.h
// Header for the generic Option type, representing an optional value.
// Brendan Dileo - 2026

#ifndef OPTION_H
#define OPTION_H

#include <stdbool.h>
#include <stddef.h>

// `present` == false means the Option holds no value; value is meaningless in that case.
// Option is passed and returned by value; it does not own value.
typedef struct Option {
    void *value;
    bool present;
} Option;

// Builds an Option holding value.
Option option_some(void *value);
// Builds an empty Option.
Option option_none(void);
// True if o is non-NULL and holds a value.
bool option_is_some(const Option *o);
// True if o is NULL or holds no value.
bool option_is_none(const Option *o);
// Returns o's value, or NULL if o is empty / NULL.
void *option_value(const Option *o);
// Returns o's value if present, otherwise default_value.
void *option_unwrap_or(const Option *o, void *default_value);

#endif
