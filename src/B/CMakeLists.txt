add_library(Bypass STATIC bypass.c)
target_link_libraries(Bypass PUBLIC BST)

target_include_directories(Bypass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})