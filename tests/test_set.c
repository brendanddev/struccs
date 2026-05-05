/**
 * test_set.c
 * The test suite for the Set implementation backed by a hash table.
 * Brendan Dileo - 2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

void print_int(void *key, void *value) {
    printf("[%d] ", * (int *) key);
}

void print_str(void *key, void *value) {
    printf("[%s] ", * (char *) key);
}

int main(void) {
    Set *set = set_create(sizeof(char *));
    printf("Set size: %d\n", set_size(set));


    char str[] = "Cat";
    char str2[] = "Cats";
    char str3[] = "Coots";
    char str4[] = "Dice";
    char str5[] = "Mice";
    char str6[] = "Lets";

    set_add(set, str);

    // for (int i = 0; i < 100; i++) {
    //     set_add(set, &i);
    // }
    // set_print(set, print_int); 

    // for (int i = 100; i < 200; i++) {
    //     set_add(set, &i);
    // }
    // set_print(set, print_int); 


    printf("Set size: %d\n", set_size(set));
    set_print(set, print_str); 
    set_discard(set);
    set = NULL;
    return 0;
}