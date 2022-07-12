#include <stdio.h>
#include "hashmap.h"

int main(void)
{
    hashmap* double_map = hashmap_init(TYPE_DOUBLE);
    hashmap* string_map = hashmap_init(TYPE_STRING);

    hashmap_add_set(double_map, "Hello", 66.6);
    hashmap_add_set(double_map, "World", 189.89);
    hashmap_add_set(double_map, "Foo", 496.666);
    hashmap_add_set(double_map, "Bar", 4564.4849421);
    hashmap_add_set(double_map, "42!", 89190.67);

    hashmap_add_set(string_map, "Viel", "aber");
    hashmap_add_set(string_map, "zu", "dafür");
    hashmap_add_set(string_map, "lange", "einiges");
    hashmap_add_set(string_map, "gebraucht", "gelernt");
    hashmap_add_set(string_map, "REUE!", "aus den Schmerzen");

    hashmap_iter(double_map);
    hashmap_iter(string_map);

    printf("\n%.1lf %s\n", hashmap_get_double(double_map, "Hello"), hashmap_get_string(string_map, "REUE!"));
    
    printf("\nFEHLSCHLAG:\n");
    printf("%s\n", hashmap_get_string(string_map, "NICHT_DA"));

    hashmap_add_set(double_map, "Hello", 42.0);
    hashmap_add_set(string_map, "REUE!", " is fun");
    printf("%.1lf %s\n", hashmap_get_double(double_map, "Hello"), hashmap_get_string(string_map, "REUE!"));

    hashmap_remove(double_map, "42!");
    hashmap_remove(double_map, "World");

    printf("\nFEHLSCHLAG:\n");
    hashmap_remove(double_map, "fail");
    printf("\n");

    printf("%lf - %lf = %lf\n\n", hashmap_get_double(double_map, "Foo"), hashmap_get_double(double_map, "Bar"), hashmap_get_double(double_map, "Foo") - hashmap_get_double(double_map, "Bar"));

    hashmap_remove(string_map, "lange");
    hashmap_remove(string_map, "zu");

    hashmap_iter(double_map);
    hashmap_iter(string_map);

    hashmap_del(double_map);
    hashmap_del(string_map);

    return 0;
}

