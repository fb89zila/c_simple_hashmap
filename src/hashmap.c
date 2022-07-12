#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hashmap_get_int(hashmap* map, char* key)
{
    void* value = __hashmap_get__(map, key);
    if (value != NULL)
        return *((int*) value);
    return 0;
}

uint32_t hashmap_get_uint(hashmap* map, char* key)
{
    void* value = __hashmap_get__(map, key);
    if (value != NULL)
        return *((uint32_t*) value);
    return 0;
}

float hashmap_get_float(hashmap* map, char* key)
{
    void* value = __hashmap_get__(map, key);
    if (value != NULL)
        return *((float*) value);
    return 0.0;
}

double hashmap_get_double(hashmap* map, char* key)
{
    void* value = __hashmap_get__(map, key);
    if (value != NULL)
        return *((double*) value);
    return 0.0;
}

char hashmap_get_char(hashmap* map, char* key)
{
    void* value = __hashmap_get__(map, key);
    if (value != NULL)
        return *((char*) value);
    return 0;
}

char* hashmap_get_string(hashmap* map, char* key)
{
    void* value = __hashmap_get__(map, key);
    if (value != NULL)
        return *((char**) value);
    return "";
}

int return_int(void* data) { return *((int*) data); }
uint32_t return_uint(void* data) { return *((uint32_t*) data); }
float return_float(void* data) { return *((float*) data); }
double return_double(void* data) { return *((double*) data); }
char return_char(void* data) { return *((char*) data); }
char* return_string(void* data) { return *((char**) data); }

void* int_to_void_ptr(hashmap* map, char* key, int data)
{
    int* data_ptr = (int*) malloc(sizeof(int));
    if (data_ptr == NULL)
    {
        fprintf(stderr, "Allocation of value data failed: Out of memory.\n");
        exit(1);
    }
    *data_ptr = data;

    __hashmap_add_set__(map, key, data_ptr);
}

void* uint_to_void_ptr(hashmap* map, char* key, uint32_t data)
{
    uint32_t* data_ptr = (uint32_t*) malloc(sizeof(uint32_t));
    if (data_ptr == NULL)
    {
        fprintf(stderr, "Allocation of value data failed: Out of memory.\n");
        exit(1);
    }
    *data_ptr = data;

    __hashmap_add_set__(map, key, data_ptr);
}

void* float_to_void_ptr(hashmap* map, char* key, float data)
{
    float* data_ptr = (float*) malloc(sizeof(float));
    if (data_ptr == NULL)
    {
        fprintf(stderr, "Allocation of value data failed: Out of memory.\n");
        exit(1);
    }
    *data_ptr = data;

    __hashmap_add_set__(map, key, data_ptr);
}

void* double_to_void_ptr(hashmap* map, char* key, double data)
{
    double* data_ptr = (double*) malloc(sizeof(double));
    if (data_ptr == NULL)
    {
        fprintf(stderr, "Allocation of value data failed: Out of memory.\n");
        exit(1);
    }
    *data_ptr = data;

    __hashmap_add_set__(map, key, data_ptr);
}

void* char_to_void_ptr(hashmap* map, char* key, char data)
{
    char* data_ptr = (char*) malloc(sizeof(char));
    if (data_ptr == NULL)
    {
        fprintf(stderr, "Allocation of value data failed: Out of memory.\n");
        exit(1);
    }
    *data_ptr = data;

    __hashmap_add_set__(map, key, data_ptr);
}

void* string_to_void_ptr(hashmap* map, char* key, char* data)
{
    char** data_ptr = (char**) malloc(sizeof(char*));
    if (data_ptr == NULL)
    {
        fprintf(stderr, "Allocation of value data failed: Out of memory.\n");
        exit(1);
    }
    *data_ptr = data;

    __hashmap_add_set__(map, key, data_ptr);
}

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

const char* get_map_type(hashmap* map)
{ return enum_type_str[map->value_type]; }

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
        {
            dest->key = (char*) calloc(strlen(key)+1, sizeof(char));
            if (dest->key == NULL)
            {
                fprintf(stderr, "Adding new key failed: Out of memory.\n");
                exit(1);
            }
        }
    else
        {
            dest->key = (char*) realloc(dest->key, strlen(key)+1);
            if (dest->key == NULL)
            {
                fprintf(stderr, "Reallocation of key failed: Out of memory.\n");
                exit(1);
            }
        }

    strcpy(dest->key, key);
}

void hashmap_copy_entry(bucket* dest, bucket* src)
{
    dest->next = src->next;
    dest->hash = src->hash;
    dest->value = src->value;
    
    if (dest->key == NULL)
        {
            dest->key = (char*) calloc(strlen(src->key)+1, sizeof(char));
            if (dest->key == NULL)
            {
                fprintf(stderr, "Adding new key failed: Out of memory.\n");
                exit(1);
            }
        }
    else
        {
            dest->key = (char*) realloc(dest->key, strlen(src->key)+1);
            if (dest->key == NULL)
            {
                fprintf(stderr, "Reallocation of key failed: Out of memory.\n");
                exit(1);
            }
        }
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

static void __hashmap_del_bucket_ll__(bucket* b)
{
    if (b->next != NULL)
        __hashmap_del_bucket_ll__(b->next);
    
    free(b);
}

void hashmap_del(hashmap* map)
{
    #ifdef DEBUG
        printf("+-------------------------------------------------------------------------------+\n");
        printf("DELETE MAP %d\n", map->value_type);
        printf("DELETE LINKED LISTS");
    #endif // DEBUG

    for (int i = 0; i < map->capacity; i++)
    {
        if ((map->bucket_list+i)->next != NULL)
        {
            #ifdef DEBUG
                printf(" %3d, ", i);;
            #endif // DEBUG

            __hashmap_del_bucket_ll__((map->bucket_list+i)->next);
        }
    }

    #ifdef DEBUG
        printf("\n+-------------------------------------------------------------------------------+\n\n");
    #endif // DEBUG

    free(map->bucket_list);
    free(map);
}

static void __hashmap_rehash__(hashmap* map, bucket* old_entry)
{
    uint32_t new_index = (u_int32_t) (old_entry->hash % map->capacity);
    
    bucket* current = map->bucket_list+new_index;

    if (current->key == NULL)
        hashmap_write_entry(current, old_entry->key, old_entry->hash, old_entry->value);
    else
    {   
        while (current->next != NULL)
            current = current->next;
        
        current->next = (bucket*) calloc(1, sizeof(bucket));
        if (current->next == NULL)
        {
            fprintf(stderr, "Allocation of bucket failed: Out of memory.\n");
            exit(1);
        }
        
        hashmap_write_entry(current->next, old_entry->key, old_entry->hash, old_entry->value);
    }
}

void hashmap_resize(hashmap* map)
{
    #ifdef DEBUG
        printf("+--------------+\n| RESIZING MAP |\n+--------------+\n\n");
    #endif // DEBUG

    bucket* old_bucket_list = map->bucket_list;
    size_t old_capacity = map->capacity;

    map->capacity *= DEFAULT_RESIZE_MULT;
    map->bucket_list = (bucket*) calloc(map->capacity, sizeof(bucket));
    if (map->bucket_list == NULL)
    {
        fprintf(stderr, "Allocating bucket list failed: Out of memory.\n");
        exit(1);
    }

    bucket* current = NULL;
    uint32_t new_index = 0;

    for (int i = 0; i < old_capacity; i++)
    {
        current = old_bucket_list+i;

        if (current->key != NULL && current->next != NULL)
        {
            __hashmap_rehash__(map, current);

            while (current->next != NULL)
            {
                __hashmap_rehash__(map, current->next);
                current = current->next;
            }

            __hashmap_del_bucket_ll__((old_bucket_list+i)->next);
        }
        else if (current->key != NULL && current->next == NULL)
            __hashmap_rehash__(map, current);
    }

    free(old_bucket_list);
}

static bucket* __hashmap_find__(hashmap* map, char* key, uint64_t hash, bucket** last_entry)
{
    uint32_t index = (u_int32_t) (hash % map->capacity);

    bucket* current = map->bucket_list+index;
    *(last_entry) = current;

    if (current->key != NULL)
    {
        if ((strcmp(current->key, key) == 0) && (current->hash == hash)) // (str1 == str2) --> strcmp == 0 
            return current;

        while (current->next != NULL)
        {
            if ((strcmp(current->next->key, key) == 0) && (current->next->hash == hash))
                return current->next;

            *(last_entry) = current->next;
            current = current->next;
        }
    }

    return NULL;
}

void* __hashmap_get__(hashmap* map, char* key)
{
    uint64_t hash = hash_string(key);

    bucket* last_entry = NULL;
    bucket* matching_bucket = __hashmap_find__(map, key, hash, &last_entry);

    if (matching_bucket != NULL)
        return matching_bucket->value;
    
    printf("Key '%s' not found.\n", key);
    return NULL;
}

static void __hashmap_add_set__(hashmap* map, char* key, void* value)
{
    if (map->size+1 > DEFAULT_LOAD * map->capacity)
        hashmap_resize(map);

    uint64_t hash = hash_string(key);

    bucket* last_entry = NULL;
    bucket* matching_bucket = __hashmap_find__(map, key, hash, &last_entry);

    if (matching_bucket != NULL)
    {
        #ifdef DEBUG
            printf("SET KEY '%s' - ", key);
            print_value(value, map->value_type);
            printf("\n");
        #endif // DEBUG
        matching_bucket->value = value;
    }
    else
    {       
        #ifdef DEBUG
            printf("CREATE KEY '%s' - ", key);
            print_value(value, map->value_type);
            printf("(map-size: %ld)\n", map->size);
        #endif // DEBUG

        if (last_entry->next == NULL && last_entry->key == NULL)
            hashmap_write_entry(last_entry, key, hash, value);
        else
        {
            bucket* new_entry = calloc(1, sizeof(bucket));
            if (new_entry == NULL)
            {
                fprintf(stderr, "Allocation of bucket failed: Out of memory.\n");
                exit(1);
            }

            hashmap_write_entry(new_entry, key, hash, value);

            last_entry->next = new_entry;
        }

        map->size++;
    }
}

bool hashmap_remove(hashmap* map, char* key)
{
    uint64_t hash = hash_string(key);

    bucket* last_entry = NULL;
    bucket* to_delete = __hashmap_find__(map, key, hash, &last_entry);

    if (to_delete == NULL)
    {
        printf("No entry with key '%s' to remove.\n", key);
        return true;
    }
    else 
    {
        #ifdef DEBUG
            printf("REMOVE KEY '%s' (map-size: %ld)\n", to_delete->key, map->size-1);
        #endif // DEBUG

        if (to_delete->next == NULL && last_entry == to_delete)
        {
            to_delete->key = NULL;
            to_delete->hash = 0;
            free(to_delete->value);
        }
        else if (to_delete->next == NULL && last_entry != to_delete)
        {
            last_entry->next = NULL;
            free(to_delete);
        }
        else if (to_delete->next != NULL && last_entry == to_delete)
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
        return false;
    }
}

void print_bucket(bucket* b, type value_type)
{
    printf("key: '%s', value: '", b->key);
    print_value(b->value, value_type);
    printf("' (hash: '%lu')\n", b->hash);

    if (b->next != NULL)
        print_bucket(b->next, value_type);
}

void hashmap_iter(hashmap* map)
{
    for (int i = 0; i < map->capacity; i++)
        if ((map->bucket_list+i)->key != NULL)
        {
            #ifdef DEBUG
                printf("-----------\nbucket: %d\n-----------\n", i);
            #endif // DEBUG
            
            print_bucket(map->bucket_list+i, map->value_type);
        }            
}
