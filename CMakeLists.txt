cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

project(hashmap VERSION 1.0)

message(STATUS ${PROJECT_BINARY_DIR})

add_library(hashmap_src src/hashmap.c)
add_executable(hashmap src/hashmap_test.c)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "hashmap_test")

target_link_libraries(hashmap PUBLIC hashmap_src)
