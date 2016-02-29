#include "collect.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TEST_STR_VALUE(test_str, expect_start, expect_len) \
{ \
    num++;\
    str = test_str; \
    start = 0; \
    len = strlen(str); \
    trim_brackets(str, &start, &len); \
    if (start == expect_start && len == expect_len) { \
       printf("STR TEST OK:\"%s\"\t\tstart = %d end = %d\n", str, start, len);  \
       ok_num++;\
    } \
    else { \
       printf("STR TEST ERROR:\"%s\"\t\tstart = %d end = %d\n", str, start, len); \
    } \
}

int main()
{
    int start, len;
    int num = 0;
    int ok_num = 0;
    start = 0;
    char *str;

    printf("\n============== TEST BEGIN ==============\n");

    TEST_STR_VALUE("(sin(2.0) * cos(30) ) ", 1, 18);
    TEST_STR_VALUE(" 1 * 12 ", 1, 6);
    TEST_STR_VALUE("  (sin(2.0) * cos(30) ) ", 3, 18);
    TEST_STR_VALUE("  (sin(2.0) * cos(30) ) ", 3, 18);
    TEST_STR_VALUE("  (sin(2.0) * cos(30) ) ", 3, 18);

    printf("============== TEST OVER ==============\n");

    printf("\n============== summry ============\n");
    printf("Test Num: %d, OK Num: %d\n", num, ok_num);
    printf("================ end =============\n");

    return 0;
}

