// option.c
// Implementation of the generic Option type, representing an optional value.
// Brendan Dileo - 2026

#include "option.h"

Option option_some(void *value) {
    Option option;
    option.value = value;
    option.present = true;
    return option;
}

Option option_none(void) {
    Option option;
    option.value = NULL;
    option.present = false;
    return option;
}

bool option_is_some(const Option *o) {
    return (o != NULL && o->present);
}

bool option_is_none(const Option *o) {
    return (o == NULL || !o->present);
}

void *option_value(const Option *o) {
    if (!option_is_some(o)) return NULL;
    return o->value;
}

void *option_unwrap_or(const Option *o, void *default_value) {
    if (!option_is_some(o)) return default_value;
    return o->value;
}
