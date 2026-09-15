// result.h
// Header for the generic Result type used for error handling.
// Brendan Dileo - 2026

#ifndef RESULT_H
#define RESULT_H

#include <stdbool.h>
#include <stddef.h>

// error == NULL means success; a non-NULL error string means failure. Result is
// passed and returned by value; it does not own value or error.
typedef struct Result {
    void *value;
    const char *error;
} Result;

// Builds a success Result carrying value.
Result result_ok(void *value);
// Builds a failure Result carrying message (borrowed; must outlive the Result).
Result result_err(const char *message);
// True if r is non-NULL and holds no error.
bool result_is_ok(const Result *r);
// True if r is NULL or holds an error.
bool result_is_err(const Result *r);
// Returns r's value, or NULL if r is an error / NULL.
void *result_value(const Result *r);
// Returns r's error string, or NULL if r is a success / NULL.
const char *result_error(const Result *r);
// Returns r's value if ok, otherwise default_value.
void *result_unwrap_or(const Result *r, void *default_value);

#endif
