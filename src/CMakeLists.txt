cmake_minimum_required(VERSION 3.10)

project(hashmap VERSION 1.0)

add_executable(hashmap hashmap.c)

target_include_directories(hashmap PUBLIC "${PROJECT_BINARY_DIR}")