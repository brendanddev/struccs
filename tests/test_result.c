// test_result.c
// Tests for the generic Result type
// Brendan Dileo - 2026

#include <stdio.h>
#include "test_utils.h"
#include "result.h"

// Prototypes
void test_result_ok(void);
void test_result_err(void);
void test_result_is_ok_is_err(void);
void test_result_value_and_error(void);
void test_result_unwrap_or(void);
void test_result_null_safety(void);

int main(void) {
    TEST(test_result_ok);
    TEST(test_result_err);
    TEST(test_result_is_ok_is_err);
    TEST(test_result_value_and_error);
    TEST(test_result_unwrap_or);
    TEST(test_result_null_safety);

    TEST_MAIN_END;
}

void test_result_ok(void) {
    int x = 42;
    Result r = result_ok(&x);

    ASSERT_TRUE(result_is_ok(&r));
    ASSERT_FALSE(result_is_err(&r));
    ASSERT_NOT_NULL(result_value(&r));
    ASSERT_NULL(result_error(&r));
    ASSERT_EQ(result_value(&r), &x);
}

void test_result_err(void) {
    Result r = result_err("something failed");

    ASSERT_TRUE(result_is_err(&r));
    ASSERT_FALSE(result_is_ok(&r));
    ASSERT_NULL(result_value(&r));
    ASSERT_NOT_NULL(result_error(&r));
}

void test_result_is_ok_is_err(void) {
    int x = 10;
    Result ok = result_ok(&x);
    Result err = result_err("error");

    ASSERT_TRUE(result_is_ok(&ok));
    ASSERT_FALSE(result_is_err(&ok));

    ASSERT_TRUE(result_is_err(&err));
    ASSERT_FALSE(result_is_ok(&err));
}

void test_result_value_and_error(void) {
    int x = 99;
    Result ok = result_ok(&x);
    Result err = result_err("failed");

    ASSERT_EQ(result_value(&ok), &x);
    ASSERT_NULL(result_error(&ok));

    ASSERT_NULL(result_value(&err));
    ASSERT_NOT_NULL(result_error(&err));
}

void test_result_unwrap_or(void) {
    int x = 10;
    int y = 20;

    Result ok = result_ok(&x);
    Result err = result_err("fail");

    ASSERT_EQ(result_unwrap_or(&ok, &y), &x);
    ASSERT_EQ(result_unwrap_or(&err, &y), &y);
}

void test_result_null_safety(void) {
    // Passing NULL should be treated as an error state
    ASSERT_FALSE(result_is_ok(NULL));
    ASSERT_TRUE(result_is_err(NULL));
    ASSERT_NULL(result_value(NULL));
    ASSERT_NULL(result_error(NULL));
}
