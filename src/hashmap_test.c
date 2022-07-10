#include "hashmap.h"
#include <stdio.h>

int main(void)
{
    hashmap* map = hashmap_init(TYPE_FLOAT);
    hashmap* str_map = hashmap_init(TYPE_STRING);
    
    char* keys[] = {"teststring", "test", "string", "teng", "testring", "testg"};
    float data[] = {5.234,        5.135,  135.133,  51535,  1555.335,   109182.12497};

    for (int i = 0; i < 6; i++)
    {
        hashmap_add_set(map, keys[i], data+i);
        hashmap_add_set(str_map, keys[i], keys+i);
    }
    
    hashmap_iter(map);
    printf("\n");
    hashmap_iter(str_map);

    printf("\n");

    hashmap_del(map);

    return 0;
}