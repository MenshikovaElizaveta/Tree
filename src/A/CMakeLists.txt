add_library(BST STATIC BST.c BST.h)

target_include_directories(BST PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})