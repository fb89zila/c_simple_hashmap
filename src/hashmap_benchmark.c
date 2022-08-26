#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "hashmap.h"
#include "random_data.h"

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

int main(int argc, char *argv[])
{
    srand((unsigned int) time(NULL));

    int entry_count = 1000;

    if (argc == 2)
    {   
        if (atoi(argv[1]) >= 0) 
            entry_count = atoi(argv[1]);
    }
    
    clock_t add_int, set_int, get_int, iter_int, resize_int, remove_int,
            start, end;

    hashmap* map_int = hashmap_init(TYPE_INT);

    char** keys = create_keys(entry_count);

    int* int_arr = create_random_int_arr(entry_count);

    // benchmark hashmap_add_set() - adding entries
    start = clock();
    for (int i = 0; i < entry_count; i++)
        hashmap_add_set(map_int, keys[i], int_arr[i]);
    end = clock();
    add_int = end - start;

    // benchmark hashmap_add_set() - setting new values
    free(int_arr);
    int_arr = create_random_int_arr(entry_count);

    start = clock();
    for (int k = 0; k < entry_count; k++)
        hashmap_add_set(map_int, keys[k], int_arr[k]);
    end = clock();
    set_int = end - start;

    //DEBUG
    //hashmap_iter(map_int);

    // benchmark hashmap_get()
    int temp_int;

    start = clock();
    for (int m = 0; m < entry_count; m++)
        temp_int = hashmap_get_int(map_int, keys[m]);
    end = clock();
    get_int = end - start;

    // benchmark hashmap_iter()
    start = clock();
    hashmap_iter(map_int);
    end = clock();
    iter_int = end - start;

    // benchmark hashmap_resize()
    start = clock();
    hashmap_resize(map_int);
    end = clock();
    resize_int = end - start;

    // benchmark hashmap_remove()

    start = clock();
    for (int o = 0; o < entry_count; o++)
        hashmap_remove(map_int, keys[o]);
    end = clock();
    remove_int = end - start;

    // write to markdown file (created by cmake)
    FILE* file = fopen("benchmark.csv", "a");

    fprintf(file, "%s,%ld,%ld,%ld,%ld,%ld,%ld,%d\n", get_map_type(map_int), add_int, set_int, get_int, iter_int, resize_int, remove_int, entry_count);

    fclose(file);

    hashmap_del(map_int);

    return 0;
}