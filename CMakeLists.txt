cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

project(hashmap VERSION 1.0)

add_library(hashmap_lib SHARED src/hashmap.c src/random_data.c)

add_executable(hashmap_test src/hashmap_test.c)
add_executable(hashmap_benchmark src/hashmap_benchmark.c)

target_link_libraries(hashmap_test PUBLIC hashmap_lib)
target_link_libraries(hashmap_benchmark PUBLIC hashmap_lib)
