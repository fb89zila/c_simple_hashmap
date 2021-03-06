#include <stdlib.h>
#include <stdint.h>
#include "random_data.h"

int* create_random_int_arr(size_t array_size)
{
    int* array = malloc(sizeof(int) * array_size);

    for (int i = 0; i < array_size; i++)
        *(array+i) = rand() - rand();

    return array;
}

uint32_t* create_random_uint_arr(size_t array_size)
{
    int* array = malloc(sizeof(uint32_t) * array_size);

    for (int i = 0; i < array_size; i++)
        *(array+i) = rand() - rand();

    return array;
}

float* create_random_float_arr(size_t array_size)
{
    float* array = malloc(sizeof(float) * array_size);

    for (int i = 0; i < array_size; i++)
        *(array+i) = (rand() / (float) RAND_MAX);

    return array;
}

double* create_random_double_arr(size_t array_size)
{
    double* array = malloc(sizeof(double) * array_size);

    for (int i = 0; i < array_size; i++)
        *(array+i) = (rand() / (double) RAND_MAX);

    return array;
}

char* create_random_char_arr(size_t array_size)
{
    char* array = malloc(sizeof(char) * array_size);

    for (int i = 0; i < array_size; i++)
        *(array+i) = CHAR_POOL[rand() % CHAR_POOL_SIZE];

    return array;
}

char** create_random_str_arr(size_t max_str_length, size_t array_size)
{
    char** array = malloc(sizeof(char*) * array_size);
    char* str;

    for (int i = 0; i < array_size; i++)
    {
        int32_t str_len = (rand() % max_str_length) + 2; // strlen + \0

        str = calloc(str_len, sizeof(char));

        for (int j = 0; j < str_len-1; j++)
            *(str+j) = CHAR_POOL[rand() % CHAR_POOL_SIZE];

        *(array+i) = str;
    }

    return array;
}