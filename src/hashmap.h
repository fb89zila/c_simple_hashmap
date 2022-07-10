#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// Capacity for initializing and resizing
#define DEFAULT_CAPACITY 16
// Defines when to resize
#define DEFAULT_LOAD 0.75f
// Defines resize multiplier
#define DEFAULT_RESIZE_MULT 2

#define return_void_ptr(n) _Generic( (n), default: &n)

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

struct bucket
{
    bucket* next;

    char* key;
    void* value;
    uint32_t hash;
};

struct hashmap
{
    bucket* bucket_list;

    type value_type;

    size_t size;
    size_t capacity;
};

// functions to return value in its intended data type

int return_int(void* data);
uint32_t return_uint(void* data);
float return_float(void* data);
double return_double(void* data);
char return_char(void* data);
char* return_string(void* data);

/* Prints value.
 *
 * @param value data pointer of value
 * @param value_type data type of the value
 */
void print_value(void* value, type value_type);

/* Hashes string key. Uses djb2 (http://www.cse.yorku.ca/~oz/hash.html)
 * 
 * @param key string key to hash
 * @return hash for given string
 */
uint64_t hash_string(char* key);

/* Writes given data to dest.
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
 * @param keytype data type of the keys
 * @param valuetype data type of the values
 * @return pointer to new hashmap
 */
hashmap* hashmap_init(type valuetype);

/* Deletes bucket.
 * 
 * @param b bucket to delete
 */
static void hashmap_del_bucket_ll(bucket* b);

/* Deletes hashmap.
 * 
 * @param map hashmap to delete
 */
void hashmap_del(hashmap* map);

/* Find given key with hash in given hashmap.
 * 
 * @param map hashmap
 * @param key searched key
 * @param hash hash of searched key
 * @param last_entry [out] last found entry in bucket
 * @return bucket with matching key and hash (NULL if no match)
 */
static bucket* hashmap_find(hashmap* map, char* key, uint64_t hash, bucket** last_entry);

/* Retrieve value for given key.
 * 
 * @param map hashmap with key
 * @param key key with value
 * @return value as void pointer
 */
void* hashmap_get(hashmap* map, char* key);

/* Add new entry to hashmap.
 * 
 * @param map hashmap for new entry
 * @param key new key
 * @param value new value
 */
void hashmap_add_set(hashmap* map, char* key, void* value);

/* Rehashes entriy
 * 
 * @param map map with new bucket_list
 * @param old_bucket entry to rehash
 */
static void hashmap_rehash(hashmap* map, bucket* old_entry);
/* Resizes hashmap by 'DEFAULT_RESIZE_MULT'
 * 
 * @param map hashmap to resize
 */
void hashmap_resize(hashmap* map);

/* Remove entry from hashmap.
 * 
 * @param map hashmap with entry
 * @param key entry to remove
 */
void hashmap_remove(hashmap* map, char* key);

/* Prints the given bucket
 * 
 * @param b bucket to print
 * @param value_type data type of the value
 */
void print_bucket(bucket* b, type value_type);

/* Iterate through hashmap.
 * 
 * @param map hashmap to iterate through
 */
void hashmap_iter(hashmap* map);

#endif // !HASHMAP_H