// test_option.c
// Tests for the generic Option type
// Brendan Dileo - 2026

#include <stdio.h>
#include "test_utils.h"
#include "option.h"

// Prototypes
void test_option_some(void);
void test_option_none(void);
void test_option_is_some_is_none(void);
void test_option_value(void);
void test_option_unwrap_or(void);
void test_option_null_safety(void);
void test_option_some_with_null_value(void);

int main(void) {
    TEST(test_option_some);
    TEST(test_option_none);
    TEST(test_option_is_some_is_none);
    TEST(test_option_value);
    TEST(test_option_unwrap_or);
    TEST(test_option_null_safety);
    TEST(test_option_some_with_null_value);

    TEST_MAIN_END;
}

void test_option_some(void) {
    int x = 42;
    Option o = option_some(&x);

    ASSERT_TRUE(option_is_some(&o));
    ASSERT_FALSE(option_is_none(&o));
    ASSERT_NOT_NULL(option_value(&o));
    ASSERT_EQ(option_value(&o), &x);
}

void test_option_none(void) {
    Option o = option_none();

    ASSERT_TRUE(option_is_none(&o));
    ASSERT_FALSE(option_is_some(&o));
    ASSERT_NULL(option_value(&o));
}

void test_option_is_some_is_none(void) {
    int x = 10;
    Option some = option_some(&x);
    Option none = option_none();

    ASSERT_TRUE(option_is_some(&some));
    ASSERT_FALSE(option_is_none(&some));

    ASSERT_TRUE(option_is_none(&none));
    ASSERT_FALSE(option_is_some(&none));
}

void test_option_value(void) {
    int x = 99;
    Option some = option_some(&x);
    Option none = option_none();

    ASSERT_EQ(option_value(&some), &x);
    ASSERT_NULL(option_value(&none));
}

void test_option_unwrap_or(void) {
    int x = 10;
    int y = 20;

    Option some = option_some(&x);
    Option none = option_none();

    ASSERT_EQ(option_unwrap_or(&some, &y), &x);
    ASSERT_EQ(option_unwrap_or(&none, &y), &y);
}

void test_option_null_safety(void) {
    // Passing NULL should be treated as an empty Option
    ASSERT_FALSE(option_is_some(NULL));
    ASSERT_TRUE(option_is_none(NULL));
    ASSERT_NULL(option_value(NULL));
}

void test_option_some_with_null_value(void) {
    // A Some explicitly holding NULL is still "present" - this is the
    // exact case present/value are separate fields for
    Option o = option_some(NULL);

    ASSERT_TRUE(option_is_some(&o));
    ASSERT_FALSE(option_is_none(&o));
    ASSERT_NULL(option_value(&o));
}
