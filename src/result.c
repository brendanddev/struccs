// result.c
// A simple Result type that pairs a value with an error message.
// Brendan Dileo - 2026

#include "result.h"

Result result_ok(void *value) {
    Result res;
    res.value = value;
    res.error = NULL;
    return res;
}

Result result_err(const char *message) {
    Result res;
    res.value = NULL;
    res.error = message;
    return res;
}

bool result_is_ok(const Result *res) {
    return res != NULL && res->error == NULL;
}

bool result_is_err(const Result *res) {
    return res == NULL || res->error != NULL;
}

void *result_value(const Result *res) {
    return result_is_ok(res) ? res->value : NULL;
}

const char *result_error(const Result *res) {
    if (res == NULL) {
        return NULL;
    }
    return res->error;
}

void *result_unwrap_or(const Result *res, void *default_value) {
    return result_is_ok(res) ? res->value : default_value;
}
