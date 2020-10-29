file(GLOB lib_source "*.cpp")
get_filename_component(dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB lib_headers "../include/${dir_name}/*.h")






add_library("${dir_name}_static" STATIC  ${lib_source})
target_include_directories("${dir_name}_static" PUBLIC "../include/")




add_library("${dir_name}_shared" SHARED  ${lib_source} ${lib_headers})
target_include_directories("${dir_name}_shared" PUBLIC "../include/")

