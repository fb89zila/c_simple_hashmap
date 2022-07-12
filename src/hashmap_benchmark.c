#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "hashmap.h"
#include "random_data.h"

#define ENTRY_COUNT 1000

int round_up(float num)
{
    int cmp = (int) num;

    if (num > cmp)
        return ++cmp;
    
    return cmp;
}

char** create_keys(size_t array_size)
{
    size_t str_size_with_null = round_up(array_size / (float) CHAR_POOL_SIZE) + 1;
    char* str;

    char** array = malloc(sizeof(char*) * array_size);
    
    int max_pos = 0;

    int remaining = array_size;
    int needed_loops = CHAR_POOL_SIZE;

    while (remaining > 0)
    {
        for (int j = 0; j < needed_loops; j++)
        {
            str = calloc(str_size_with_null, sizeof(char));

            for (int i = 0; i <= max_pos; i++)
            {
                *(str+i) = CHAR_POOL[j];
            }

            *(array+j+(61 * max_pos)) = str;
        }
        
        remaining -= needed_loops;

        if (remaining <= CHAR_POOL_SIZE)
            needed_loops = remaining;

        max_pos++;
    }
    
    return array;
}

int main()
{
    srand((unsigned int) time(NULL));

    clock_t add_int, set_int, get_int, iter_int, resize_int, remove_int,
            add_str, set_str, get_str, iter_str, resize_str, remove_str,
            start, end;

    hashmap* map_int = hashmap_init(TYPE_INT);
    hashmap* map_str = hashmap_init(TYPE_STRING);

    char** keys = create_keys(ENTRY_COUNT);

    int* int_arr = create_random_int_arr(ENTRY_COUNT);
    char** str_arr = create_random_str_arr(20, ENTRY_COUNT);

    // benchmark hashmap_add_set() - adding entries
    start = clock();
    for (int i = 0; i < ENTRY_COUNT; i++)
        hashmap_add_set(map_int, keys[i], int_arr[i]);
    end = clock();
    add_int = end - start;

    start = clock();
    for (int j = 0; j < ENTRY_COUNT; j++)
        hashmap_add_set(map_str, keys[j], str_arr[j]);
    end = clock();
    add_str = end - start;

    // benchmark hashmap_add_set() - setting new values
    free(int_arr);
    free(str_arr);
    int_arr = create_random_int_arr(ENTRY_COUNT);
    str_arr = create_random_str_arr(20, ENTRY_COUNT);

    start = clock();
    for (int k = 0; k < ENTRY_COUNT; k++)
        hashmap_add_set(map_int, keys[k], int_arr[k]);
    end = clock();
    set_int = end - start;

    start = clock();
    for (int l = 0; l < ENTRY_COUNT; l++)
        hashmap_add_set(map_str, keys[l], str_arr[l]);
    end = clock();
    set_str = end - start;

    //DEBUG
    //hashmap_iter(map_int);

    // benchmark hashmap_get()
    int temp_int;
    char* temp_str;

    start = clock();
    for (int m = 0; m < ENTRY_COUNT; m++)
        temp_int = hashmap_get_int(map_int, keys[m]);
    end = clock();
    get_int = end - start;

    start = clock();
    for (int n = 0; n < ENTRY_COUNT; n++)
        temp_str = hashmap_get_string(map_str, keys[n]);
    end = clock();
    get_str = end - start;

    // benchmark hashmap_iter()
    start = clock();
    hashmap_iter(map_int);
    end = clock();
    iter_int = end - start;

    start = clock();
    hashmap_iter(map_str);
    end = clock();
    iter_str = end - start;

    // benchmark hashmap_resize()
    start = clock();
    hashmap_resize(map_int);
    end = clock();
    resize_int = end - start;

    start = clock();
    hashmap_resize(map_str);
    end = clock();
    resize_str = end - start;

    // benchmark hashmap_remove()

    start = clock();
    for (int o = 0; o < ENTRY_COUNT; o++)
        hashmap_remove(map_int, keys[o]);
    end = clock();
    remove_int = end - start;

    start = clock();
    for (int p = 0; p < ENTRY_COUNT; p++)
        hashmap_remove(map_str, keys[p]);
    end = clock();
    remove_str = end - start;

    // write to markdown file (created by cmake)
    FILE* file = fopen("benchmark.csv", "a");

    fprintf(file, "%s,%ld,%ld,%ld,%ld,%ld,%ld\n", get_map_type(map_int), add_int, set_int, get_int, iter_int, resize_int, remove_int);
    fprintf(file, "%s,%ld,%ld,%ld,%ld,%ld,%ld\n", get_map_type(map_str), add_str, set_str, get_str, iter_str, resize_str, remove_str);

    fclose(file);

    hashmap_del(map_int);
    hashmap_del(map_str);

    return 0;
}