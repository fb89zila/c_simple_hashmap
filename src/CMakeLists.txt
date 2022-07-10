cmake_minimum_required(VERSION 3.10)

project(hashmap VERSION 1.0)

add_library(hashmap_src hashmap.c)
add_executable(hashmap hashmap_test.c)

target_link_libraries(hashmap PUBLIC hashmap_src)
target_include_directories(hashmap PUBLIC "${PROJECT_BINARY_DIR}")