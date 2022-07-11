add_library(hashmap_src hashmap.c)
add_executable(hashmap hashmap_test.c)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "hashmap_test")

target_link_libraries(hashmap PUBLIC hashmap_src)
target_include_directories(hashmap PUBLIC "${PROJECT_BINARY_DIR}")