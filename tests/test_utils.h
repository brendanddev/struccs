// test_utils.h
// Lightweight test macros for struccs test suites
// Brendan Dileo - 2026

static int g_test_failures = 0;

#define ASSERT_EQ(actual, expected) \
    if ((actual) != (expected)) { \
        printf("  FAIL [%s:%d] expected %d got %d\n", \
            __func__, __LINE__, (expected), (actual)); \
        g_test_failures++; \
    }

#define ASSERT_TRUE(expr) \
    if (!(expr)) { \
        printf("  FAIL [%s:%d] expected true\n", __func__, __LINE__); \
        g_test_failures++; \
    }

#define ASSERT_FALSE(expr) \
    if ((expr)) { \
        printf("  FAIL [%s:%d] expected false\n", __func__, __LINE__); \
        g_test_failures++; \
    }

#define ASSERT_NOT_NULL(ptr) \
    if ((ptr) == NULL) { \
        printf("  FAIL [%s:%d] expected non-null pointer\n", __func__, __LINE__); \
        g_test_failures++; \
    }

#define ASSERT_NULL(ptr) \
    if ((ptr) != NULL) { \
        printf("  FAIL [%s:%d] expected null pointer\n", __func__, __LINE__); \
        g_test_failures++; \
    }

#define TEST(name) \
    printf("Running %s...\n", #name); \
    name(); \
    printf("  done\n");

#define TEST_MAIN_END return (g_test_failures > 0) ? 1 : 0
