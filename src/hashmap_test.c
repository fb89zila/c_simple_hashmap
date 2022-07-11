#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random_data.h"

#define ARRAY_SIZE 100
#define HASHMAP_SIZE 20

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
    char** keys = create_random_str_arr(50, ARRAY_SIZE);
    int* ints = create_random_int_arr(ARRAY_SIZE);
    uint32_t* uints = create_random_uint_arr(ARRAY_SIZE);
    float* floats = create_random_float_arr(ARRAY_SIZE);
    double* doubles = create_random_double_arr(ARRAY_SIZE);
    char* chars = create_random_char_arr(ARRAY_SIZE);
    char** strings = create_random_str_arr(50, ARRAY_SIZE);

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
        hashmap_iter(map_arr[j]);
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