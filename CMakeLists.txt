cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

project(hashmap VERSION 1.0)

file(WRITE ${PROJECT_BINARY_DIR}/benchmark.csv "type of hashmap,hashmap_add_set() [add],hashmap_add_set() [set],get(),iter(),resize(),remove()\n")

add_library(hashmap_lib SHARED src/hashmap.c src/random_data.c)

add_executable(hashmap_demo src/hashmap_demo.c)
add_executable(hashmap_test src/hashmap_test.c)
add_executable(hashmap_benchmark src/hashmap_benchmark.c)

target_link_libraries(hashmap_demo PUBLIC hashmap_lib)
target_link_libraries(hashmap_test PUBLIC hashmap_lib)
target_link_libraries(hashmap_benchmark PUBLIC hashmap_lib)
