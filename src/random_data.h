#ifndef RANDOM_DATA_H
#define RANDOM_DATA_H

#define CHAR_POOL "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789"
#define CHAR_POOL_SIZE 61

/* create random ints
 * 
 * @param array_size number of values to create
 */
int* create_random_int_arr(size_t array_size);

/* create random uint32_t's
 * 
 * @param array_size number of values to create
 */
uint32_t* create_random_uint_arr(size_t array_size);

/* create random floats
 * 
 * @param array_size number of values to create
 */
float* create_random_float_arr(size_t array_size);

/*create random doubles
 * 
 * @param array_size number of values to create
 */
double* create_random_double_arr(size_t array_size);

/* create random chars
 * 
 * @param array_size number of values to create
 */
char* create_random_char_arr(size_t array_size);

/* create random strings
 *
 * @param max_str_length maximum length of the strings (without \0)
 * @param array_size number of strings to create
 */
char** create_random_str_arr(size_t max_str_length, size_t array_size);

#endif // RANDOM_DATA_H