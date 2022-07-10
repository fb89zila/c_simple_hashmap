#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int return_int(void* data) {return *((int*) data);}
uint32_t return_uint(void* data) {return *((uint32_t*) data);}
float return_float(void* data) {return *((float*) data);}
double return_double(void* data) {return *((double*) data);}
char return_char(void* data) {return *((char*) data);}
char* return_string(void* data) {return *((char**) data);}

void print_value(void* value, type value_type)
{
    switch (value_type)
    {
        case TYPE_INT:
            printf("%d", return_int(value));
            break;
        case TYPE_UINT:
            printf("%u", return_uint(value));
            break;
        case TYPE_FLOAT:
            printf("%f", return_float(value));
            break;
        case TYPE_DOUBLE:
            printf("%lf", return_double(value));
            break;
        case TYPE_CHAR:
            printf("%c", return_char(value));
            break;
        case TYPE_STRING:
            printf("%s", return_string(value));
            break;
        default:
            break;
    }
}

uint64_t hash_string(char* key)
{
    uint64_t hash = 5381;
    int c;

    while (c = *key++)
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

void hashmap_write_entry(bucket* dest, char* key, uint64_t hash, void* value)
{
    dest->next = NULL;
    dest->hash = hash;
    dest->value = value;
    
    if (dest->key == NULL)
        dest->key = malloc(strlen(key)*sizeof(char));
    else
        dest->key = realloc(dest->key, strlen(key));

    strcpy(dest->key, key);
}

void hashmap_copy_entry(bucket* dest, bucket* src)
{
    dest->next = src->next;
    dest->hash = src->hash;
    dest->value = src->value;
    
    if (dest->key == NULL)
        dest->key = malloc(strlen(src->key)*sizeof(char));
    else
        dest->key = realloc(dest->key, strlen(src->key));

    strcpy(dest->key, src->key);
}

hashmap* hashmap_init(type valuetype)
{
    hashmap* map = (hashmap*) malloc(sizeof(hashmap));
    if (map == NULL)
    {
        fprintf(stderr, "Allocating hashmap failed: Out of memory.\n");
        exit(1);
    }

    map->value_type = valuetype;
    map->capacity = DEFAULT_CAPACITY;
    map->size = 0;

    map->bucket_list = (bucket*) calloc(DEFAULT_CAPACITY, sizeof(bucket));
    if (map->bucket_list == NULL)
    {
        fprintf(stderr, "Allocating bucket list failed: Out of memory.\n");
        exit(1);
    }

    return map;
}

static void hashmap_del_bucket_ll(bucket* b)
{
    if (b->next != NULL)
        hashmap_del_bucket_ll(b->next);
    
    free(b);
}

void hashmap_del(hashmap* map)
{
    for (int i = 0; i < map->capacity; i++)
        if ((map->bucket_list+i)->next != NULL)
            hashmap_del_bucket_ll((map->bucket_list+i)->next);

    free(map->bucket_list);
    free(map);
}

static void hashmap_rehash(hashmap* map, bucket* old_entry)
{
    uint32_t new_index = (u_int32_t) old_entry->hash % map->capacity;
    
    bucket* current = map->bucket_list+new_index;

    if (current->key == NULL)
        hashmap_write_entry(current, old_entry->key, old_entry->hash, old_entry->value);
    else
    {   
        while (current->next != NULL)
            current = current->next;
        
        current->next = (bucket*) malloc(sizeof(bucket));
        hashmap_write_entry(current->next, old_entry->key, old_entry->hash, old_entry->value);
    }

}

void hashmap_resize(hashmap* map)
{
    #ifdef DEBUG
        printf("+--------------+\n| RESIZING MAP |\n+--------------+\n\n");
    #endif

    bucket* old_bucket_list = map->bucket_list;
    size_t old_capacity = map->capacity;

    map->capacity *= DEFAULT_RESIZE_MULT;
    map->bucket_list = (bucket*) calloc(map->capacity, sizeof(bucket));

    bucket* current = NULL;
    uint32_t new_index = 0;

    for (int i = 0; i < old_capacity; i++)
    {
        current = old_bucket_list+i;

        if (current->key != NULL && current->next != NULL)
        {
            hashmap_rehash(map, current);

            while (current->next != NULL)
            {
                hashmap_rehash(map, current->next);
                current = current->next;
            }

            hashmap_del_bucket_ll((old_bucket_list+i)->next);
        }
        else if (current->key != NULL && current->next == NULL)
        {
            hashmap_rehash(map, current);
        }   
    }

    free(old_bucket_list);
}

static bucket* hashmap_find(hashmap* map, char* key, uint64_t hash, bucket** last_entry)
{
    uint32_t index = (u_int32_t) hash % map->capacity;

    bucket* current = map->bucket_list+index;
    
    while (1)
    {
        if (current->key == NULL)
        {
            *(last_entry) = current;
            return NULL;
        }

        if (strcmp(current->key, key) && current->hash == hash)
            return current;

        if (current->next != NULL)
            current = current->next;
        else
        {
            *(last_entry) = current;
            return NULL;
        }
    }
}

void* hashmap_get(hashmap* map, char* key)
{
    uint64_t hash = hash_string(key);

    bucket* last_entry = NULL;
    bucket* matching_bucket = hashmap_find(map, key, hash, &last_entry);

    if (matching_bucket != NULL)
        return matching_bucket->value;
    
    printf("Key %s not found.\n", key);
    return NULL;
}

void hashmap_add_set(hashmap* map, char* key, void* value)
{
    if (map->size++ > DEFAULT_LOAD * map->capacity)
        hashmap_resize(map);

    uint64_t hash = hash_string(key);

    bucket* last_entry = NULL;
    bucket* matching_bucket = hashmap_find(map, key, hash, &last_entry);

    if (matching_bucket != NULL)
        matching_bucket->value = value;
    else
    {       
        if (last_entry != NULL && last_entry->key == NULL)
            hashmap_write_entry(last_entry, key, hash, value);
        else
        {
            bucket* new_entry = malloc(sizeof(bucket));
            if (new_entry == NULL)
            {
                fprintf(stderr, "Adding new key failed: Out of memory.\n");
                exit(1);
            }

            hashmap_write_entry(new_entry, key, hash, value);
            
            last_entry->next = new_entry;
        }
    }
}

void hashmap_remove(hashmap* map, char* key)
{
    uint64_t hash = hash_string(key);

    bucket* last_entry = NULL;
    bucket* to_delete = hashmap_find(map, key, hash, &last_entry);

    if (to_delete == NULL)
        printf("No entry with key %s\n", key);
    else 
    {
        if (last_entry == NULL)
        {
            bucket* next_entry = to_delete->next;
            hashmap_copy_entry(to_delete, next_entry);
            free(next_entry);
        }
        else
        {
            last_entry->next = to_delete->next;
            free(to_delete);
        }

        map->size -= 1;
    }
}

void print_bucket(bucket* b, type value_type)
{
    printf("key: %s, value: ", b->key);
    print_value(b->value, value_type);
    printf(" (hash: %d)\n", b->hash);

    if (b->next != NULL)
        print_bucket(b->next, value_type);
}

void hashmap_iter(hashmap* map)
{
    for (int i = 0; i < map->capacity; i++)
        if ((map->bucket_list+i)->key != NULL)
        {
            #ifdef DEBUG
                printf("bucket: %d\n", i);
            #endif
            
            print_bucket(map->bucket_list+i, map->value_type);
        }            
}
