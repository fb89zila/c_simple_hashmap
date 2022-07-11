#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CHAR_POOL "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789"
#define ARRAY_SIZE 100
#define HASHMAP_SIZE 20

int* create_random_int_arr()
{
    int* array = malloc(sizeof(int) * ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++)
        *(array+i) = rand() - rand();

    return array;
}

uint32_t* create_random_uint_arr()
{
    int* array = malloc(sizeof(uint32_t) * ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++)
        *(array+i) = rand() - rand();

    return array;
}

float* create_random_float_arr()
{
    float* array = malloc(sizeof(float) * ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++)
        *(array+i) = (rand() / (float) RAND_MAX);

    return array;
}

double* create_random_double_arr()
{
    double* array = malloc(sizeof(double) * ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++)
        *(array+i) = (rand() / (double) RAND_MAX);

    return array;
}

char* create_random_char_arr()
{
    int CHAR_POOL_SIZE = strlen(CHAR_POOL);
    char* array = malloc(sizeof(char) * ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++)
        *(array+i) = CHAR_POOL[rand() % CHAR_POOL_SIZE];

    return array;
}

char** create_random_str_arr(size_t max_str_length)
{   
    int CHAR_POOL_SIZE = strlen(CHAR_POOL);
    char** array = malloc(sizeof(char*) * ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        int32_t str_len = rand() % max_str_length;

        if (str_len < 2)
            str_len = 2;

        char* str = malloc(sizeof(char) * str_len);

        for (int j = 0; j < str_len-1; j++)
            *(str+j) = CHAR_POOL[rand() % CHAR_POOL_SIZE];
        str[str_len-1] = 0;

        *(array+i) = str;
    }

    return array;
}

int main(void)
{
    srand ((unsigned int) time (NULL));

    // create hashmaps
    hashmap* map_arr[] = {
        hashmap_init(TYPE_INT),
        hashmap_init(TYPE_UINT),
        hashmap_init(TYPE_FLOAT),
        hashmap_init(TYPE_DOUBLE),
        hashmap_init(TYPE_CHAR),
        hashmap_init(TYPE_STRING)
    };

    // create random keys and values
    char** keys = create_random_str_arr(50);
    int* ints = create_random_int_arr();
    uint32_t* uints = create_random_uint_arr();
    float* floats = create_random_float_arr();
    double* doubles = create_random_double_arr();
    char* chars = create_random_char_arr();
    char** strings = create_random_str_arr(50);

    // fill hashmaps with data
    for (int i = 0; i < HASHMAP_SIZE; i++)
    {
        hashmap_add_set(map_arr[0], keys[i], ints[i]);
        hashmap_add_set(map_arr[1], keys[i], uints[i]);
        hashmap_add_set(map_arr[2], keys[i], floats[i]);
        hashmap_add_set(map_arr[3], keys[i], doubles[i]);
        hashmap_add_set(map_arr[4], keys[i], chars[i]);
        hashmap_add_set(map_arr[5], keys[i], strings[i]);
    }
    
    // iterate though hashmaps
    for (int j = 0; j < 6; j++)
    {
        hashmap_iter(map_arr[j]); printf("\n");
        printf("\n");
        hashmap_del(map_arr[j]);
    }

    // create array for hashmap_remove() test
    char* keys_rm_array[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "p", "q", "r"};
    int vals_rm_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    hashmap* rm_map = hashmap_init(TYPE_INT);

    for (int k = 0; k < 13; k++)
        hashmap_add_set(rm_map, keys_rm_array[k], vals_rm_array[k]);

    // remove entries
    hashmap_iter(rm_map);
    hashmap_add_set(rm_map, "a", 100);
    printf("remove() = %d\n", hashmap_get_int(rm_map, "a"));
    hashmap_remove(rm_map, "a");
    hashmap_remove(rm_map, "r");
    hashmap_iter(rm_map);

    // delete rm_map
    hashmap_del(rm_map);

    return 0;
}