// test_str.c
// Tests for the String type
// Brendan Dileo - 2026

#include <stdio.h>
#include <string.h>
#include "test_utils.h"
#include "str.h"

// Prototypes
void test_str_create_empty(void);
void test_str_create_with_content(void);
void test_str_create_null(void);
void test_str_append(void);
void test_str_append_empty(void);
void test_str_append_triggers_resize(void);
void test_str_contains(void);
void test_str_contains_not_found(void);
void test_str_compare(void);
void test_str_equals(void);
void test_str_copy(void);
void test_str_concat(void);
void test_str_to_upper(void);
void test_str_to_lower(void);
void test_str_trim(void);
void test_str_length_and_len(void);
void test_str_discard_null(void);
void test_str_stress_append(void);
void test_str_null_inputs(void);

int main(void) {
    TEST(test_str_create_empty);
    TEST(test_str_create_with_content);
    TEST(test_str_create_null);
    TEST(test_str_append);
    TEST(test_str_append_empty);
    TEST(test_str_append_triggers_resize);
    TEST(test_str_contains);
    TEST(test_str_contains_not_found);
    TEST(test_str_compare);
    TEST(test_str_equals);
    TEST(test_str_copy);
    TEST(test_str_concat);
    TEST(test_str_to_upper);
    TEST(test_str_to_lower);
    TEST(test_str_trim);
    TEST(test_str_length_and_len);
    TEST(test_str_discard_null);
    TEST(test_str_stress_append);
    TEST(test_str_null_inputs);

    return 0;
}

void test_str_create_empty(void) {
    String *s = str_create(NULL);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(str_len(s), 0);
    ASSERT_TRUE(s->data[0] == '\0');
    str_discard(s);
}

void test_str_create_with_content(void) {
    String *s = str_create("hello");
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(str_len(s), 5);
    ASSERT_TRUE(strcmp(s->data, "hello") == 0);
    str_discard(s);
}

void test_str_create_null(void) {
    String *s = str_create(NULL);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(str_len(s), 0);
    str_discard(s);
}

void test_str_append(void) {
    String *s = str_create("hello");
    ASSERT_TRUE(str_append(s, " world"));
    ASSERT_EQ(str_len(s), 11);
    ASSERT_TRUE(strcmp(s->data, "hello world") == 0);
    str_discard(s);
}

void test_str_append_empty(void) {
    String *s = str_create("test");
    ASSERT_TRUE(str_append(s, ""));
    ASSERT_EQ(str_len(s), 4);
    ASSERT_TRUE(strcmp(s->data, "test") == 0);
    str_discard(s);
}

void test_str_append_triggers_resize(void) {
    String *s = str_create("a");
    for (int i = 0; i < 100; i++) {
        ASSERT_TRUE(str_append(s, "x"));
    }
    ASSERT_EQ(str_len(s), 101);
    str_discard(s);
}

void test_str_contains(void) {
    String *s = str_create("hello world");
    ASSERT_TRUE(str_contains(s, "hello"));
    ASSERT_TRUE(str_contains(s, "world"));
    ASSERT_TRUE(str_contains(s, "lo wo"));
    ASSERT_FALSE(str_contains(s, ""));  // empty substring is usually considered found
    str_discard(s);
}

void test_str_contains_not_found(void) {
    String *s = str_create("hello");
    ASSERT_FALSE(str_contains(s, "xyz"));
    ASSERT_FALSE(str_contains(s, "helloo"));
    str_discard(s);
}

void test_str_compare(void) {
    String *a = str_create("apple");
    String *b = str_create("banana");
    String *c = str_create("apple");

    ASSERT_TRUE(str_compare(a, b) < 0);
    ASSERT_TRUE(str_compare(b, a) > 0);
    ASSERT_EQ(str_compare(a, c), 0);

    str_discard(a);
    str_discard(b);
    str_discard(c);
}

void test_str_equals(void) {
    String *a = str_create("test");
    String *b = str_create("test");
    String *c = str_create("Test");

    ASSERT_TRUE(str_equals(a, b));
    ASSERT_FALSE(str_equals(a, c));

    str_discard(a);
    str_discard(b);
    str_discard(c);
}

void test_str_copy(void) {
    String *orig = str_create("copy me");
    String *copy = str_copy(orig);

    ASSERT_NOT_NULL(copy);
    ASSERT_TRUE(str_equals(orig, copy));
    ASSERT_TRUE(orig->data != copy->data);   // different buffers

    str_discard(orig);
    str_discard(copy);
}

void test_str_concat(void) {
    String *a = str_create("hello");
    String *b = str_create(" world");
    String *c = str_concat(a, b);

    ASSERT_NOT_NULL(c);
    ASSERT_EQ(str_len(c), 11);
    ASSERT_TRUE(strcmp(c->data, "hello world") == 0);

    str_discard(a);
    str_discard(b);
    str_discard(c);
}

void test_str_to_upper(void) {
    String *s = str_create("Hello World 123");
    String *upper = str_to_upper(s);

    ASSERT_NOT_NULL(upper);
    ASSERT_TRUE(strcmp(upper->data, "HELLO WORLD 123") == 0);

    str_discard(s);
    str_discard(upper);
}

void test_str_to_lower(void) {
    String *s = str_create("Hello World 123");
    String *lower = str_to_lower(s);

    ASSERT_NOT_NULL(lower);
    ASSERT_TRUE(strcmp(lower->data, "hello world 123") == 0);

    str_discard(s);
    str_discard(lower);
}

void test_str_trim(void) {
    String *s = str_create("  hello world  \t\n");
    String *trimmed = str_trim(s);

    ASSERT_NOT_NULL(trimmed);
    ASSERT_TRUE(strcmp(trimmed->data, "hello world") == 0);
    ASSERT_EQ(str_len(trimmed), 11);

    str_discard(s);
    str_discard(trimmed);
}

void test_str_length_and_len(void) {
    ASSERT_EQ(str_length("hello"), 5);
    ASSERT_EQ(str_length(""), 0);

    String *s = str_create("testing");
    ASSERT_EQ(str_len(s), 7);
    ASSERT_EQ(str_length(s->data), 7);

    str_discard(s);
}

void test_str_discard_null(void) {
    str_discard(NULL);
    ASSERT_TRUE(1); // just for assertion
}

void test_str_stress_append(void) {
    String *s = str_create(NULL);

    for (int i = 0; i < 1000; i++) {
        ASSERT_TRUE(str_append(s, "a"));
    }
    ASSERT_EQ(str_len(s), 1000);

    for (int i = 0; i < 500; i++) {
        ASSERT_TRUE(str_append(s, "bc"));
    }
    ASSERT_EQ(str_len(s), 2000);

    str_discard(s);
}

void test_str_null_inputs(void) {
    ASSERT_NULL(str_copy(NULL)); // should not crash
    ASSERT_NULL(str_concat(NULL, NULL));
    ASSERT_NULL(str_to_upper(NULL));
    ASSERT_NULL(str_to_lower(NULL));
    ASSERT_NULL(str_trim(NULL));
}
