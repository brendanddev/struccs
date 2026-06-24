// Lightweight test macros for struccs test suites

#define ASSERT_EQ(actual, expected) \
    if ((actual) != (expected)) { \
        printf("  FAIL [%s:%d] expected %d got %d\n", \
            __func__, __LINE__, (expected), (actual)); \
    }

#define ASSERT_TRUE(expr) \
    if (!(expr)) { \
        printf("  FAIL [%s:%d] expected true\n", __func__, __LINE__); \
    }

#define ASSERT_FALSE(expr) \
    if ((expr)) { \
        printf("  FAIL [%s:%d] expected false\n", __func__, __LINE__); \
    }

#define ASSERT_NOT_NULL(ptr) \
    if ((ptr) == NULL) { \
        printf("  FAIL [%s:%d] expected non-null pointer\n", __func__, __LINE__); \
    }

#define ASSERT_NULL(ptr) \
    if ((ptr) != NULL) { \
        printf("  FAIL [%s:%d] expected null pointer\n", __func__, __LINE__); \
    }

#define TEST(name) \
    printf("Running %s...\n", #name); \
    name(); \
    printf("  done\n");