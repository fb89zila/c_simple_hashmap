#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// Debug switch
//#define DEBUG

// Capacity for initializing and resizing
#define DEFAULT_CAPACITY 16
// Defines when to resize
#define DEFAULT_LOAD 0.75f
// Defines resize multiplier
#define DEFAULT_RESIZE_MULT 2

// Generic for casting incomming values to void pointers
#define hashmap_add_set(map, key, value) _Generic((value), \
int: int_to_void_ptr, \
uint32_t: uint_to_void_ptr, \
float: float_to_void_ptr, \
double: double_to_void_ptr, \
char: char_to_void_ptr, \
char*: string_to_void_ptr \
) ((map), (key), (value))

// Possible data types of the values
typedef enum type type;

typedef struct bucket bucket;
typedef struct hashmap hashmap;

enum type
{
    TYPE_INT,
    TYPE_UINT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING
};

// string representations of the enum type
static const char* enum_type_str[] = {"TYPE_INT", "TYPE_UINT", "TYPE_FLOAT", "TYPE_DOUBLE", "TYPE_CHAR", "TYPE_STRING"};

struct bucket
{
    bucket* next;

    char* key;
    void* value;
    uint64_t hash;
};

struct hashmap
{
    bucket* bucket_list;

    type value_type;

    size_t size;
    size_t capacity;
};

// hashmap_get() for specific data types

int hashmap_get_int(hashmap* map, char* key);
uint32_t hashmap_get_uint(hashmap* map, char* key);
float hashmap_get_float(hashmap* map, char* key);
double hashmap_get_double(hashmap* map, char* key);
char hashmap_get_char(hashmap* map, char* key);
char* hashmap_get_string(hashmap* map, char* key);

// return a void pointer as a specific data types

int return_int(void* data);
uint32_t return_uint(void* data);
float return_float(void* data);
double return_double(void* data);
char return_char(void* data);
char* return_string(void* data);

// values -> void pointer (see hashmap_add_set())

void* int_to_void_ptr(hashmap* map, char* key, int data);
void* uint_to_void_ptr(hashmap* map, char* key, uint32_t data);
void* float_to_void_ptr(hashmap* map, char* key, float data);
void* double_to_void_ptr(hashmap* map, char* key, double data);
void* char_to_void_ptr(hashmap* map, char* key, char data);
void* string_to_void_ptr(hashmap* map, char* key, char* data);

/* Prints value.
 *
 * @param value data pointer of value
 * @param value_type data type of the value
 */
void print_value(void* value, type value_type);

/* Get data type of the values in given hashmap.
 *
 * @param map hashmap to look up
 * return string representation of the value-data type
 */
const char* get_map_type(hashmap* map);

/* Hashes string key. Uses djb2 (http://www.cse.yorku.ca/~oz/hash.html)
 * 
 * @param key key to hash
 * @return hash for given string
 */
uint64_t hash_string(char* key);

/* Writes given data to dest. (->next = NULL)
 * 
 * @param dest destination entry
 * @param key key to write
 * @param hash hash to write
 * @param value value to write
 */
void hashmap_write_entry(bucket* dest, char* key,
                         uint64_t hash, void* value);

/* Copies data of src to dest.
 * 
 * @param dest destination entry
 * @param src source entry
 */
void hashmap_copy_entry(bucket* dest, bucket* src);

/* Initializes new hashmap.
 * 
 * @param valuetype data type of the values
 * @return pointer to new hashmap
 */
hashmap* hashmap_init(type valuetype);

/* Deletes bucket.
 * 
 * @param b bucket to delete
 */
static void __hashmap_del_bucket_ll__(bucket* b);

/* Deletes hashmap.
 * 
 * @param map hashmap to delete
 */
void hashmap_del(hashmap* map);

/* Rehashes entry.
 * 
 * @param map map with new bucket_list
 * @param old_bucket entry to rehash
 */
static void __hashmap_rehash__(hashmap* map, bucket* old_entry);

/* Resizes hashmap by 'DEFAULT_RESIZE_MULT'.
 * 
 * @param map hashmap to resize
 */
void hashmap_resize(hashmap* map);

/* Find key in given hashmap.
 * 
 * @param map hashmap
 * @param key searched key
 * @param hash hash of searched key
 * @param last_entry <out> last found entry in bucket (first if empty and no ->next)
 * @return bucket with matching key and hash (NULL if no match)
 */
static bucket* __hashmap_find__(hashmap* map, char* key, uint64_t hash, bucket** last_entry);

/* Retrieve value for given key.
 * 
 * @param map hashmap with key
 * @param key searched key
 * @return value as void pointer
 */
void* __hashmap_get__(hashmap* map, char* key);

/* Add new entry to hashmap or overwrite value if the key exists.
 * 
 * @param map hashmap for new pair / value
 * @param key new key / key with value to overwrite
 * @param value new value
 */
static void __hashmap_add_set__(hashmap* map, char* key, void* value);

/* Remove entry from hashmap.
 * 
 * @param map hashmap with entry
 * @param key key for entry to remove
 * @return false/0 (no error) if successful
 */
bool hashmap_remove(hashmap* map, char* key);

/* Prints the given bucket.
 * 
 * @param b bucket to print
 * @param value_type data type of the value
 */
void print_bucket(bucket* b, type value_type);

/* Iterate through hashmap and print all entries.
 * 
 * @param map hashmap to iterate through
 */
void hashmap_iter(hashmap* map);

#endif // !HASHMAP_H