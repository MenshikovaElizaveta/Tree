add_library(Statistics STATIC statistics.c)
target_link_libraries(Statistics PUBLIC BST)

target_include_directories(Statistics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})