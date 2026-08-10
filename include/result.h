// result.h
// Header for the generic Result type used for error handling.
// Brendan Dileo - 2026

#ifndef RESULT_H
#define RESULT_H

#include <stdbool.h>
#include <stddef.h>

// Result is only valid when error == NULL
// NULL means success
typedef struct Result {
    void *value;
    const char *error;
} Result;

Result result_ok(void *value);
Result result_err(const char *message);
bool result_is_ok(const Result *r);
bool result_is_err(const Result *r);
void *result_value(const Result *r);
const char *result_error(const Result *r);
void *result_unwrap_or(const Result *r, void *default_value);

#endif
