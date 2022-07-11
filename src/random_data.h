#ifndef RANDOM_DATA_H
#define RANDOM_DATA_H

#define CHAR_POOL "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789"

// create random ints
int* create_random_int_arr(size_t array_size);

// create random uint32_t's
uint32_t* create_random_uint_arr(size_t array_size);

// create random floats
float* create_random_float_arr(size_t array_size);

// create random doubles
double* create_random_double_arr(size_t array_size);

// create random chars
char* create_random_char_arr(size_t array_size);

// create random strings
char** create_random_str_arr(size_t max_str_length, size_t array_size);

#endif // RANDOM_DATA_H