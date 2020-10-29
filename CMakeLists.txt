cmake_minimum_required(VERSION 3.12)


project(IZ_2_18)

set(STATIC_LIB_PROJECT with_static)
set(SHARED_LIB_PROJECT with_shared)

### Test definitions ###
##

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()




if ("${TARGET_CPU}" STREQUAL "amd64")
    set (CMAKE_SIZEOF_VOID_P 8)

    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)
    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS FALSE)
elseif ("${TARGET_CPU}" STREQUAL "x86")
    set (CMAKE_SIZEOF_VOID_P 4)

    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)
    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS TRUE)

    if (GCC)
        
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
        set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32")
        add_compile_options(-Wall -Werror -Wpedantic)
    endif ()
else ()
    message (FATAL_ERROR "Unsupported CPU: ${TARGET_CPU}")
endif()

file(GLOB sources "src/*.cpp")



add_subdirectory(src/neq_max_seq)

add_subdirectory(tests)



add_executable("${STATIC_LIB_PROJECT}" ${sources})
target_link_libraries("${STATIC_LIB_PROJECT}" neq_max_seq_static )
target_include_directories("${STATIC_LIB_PROJECT}" PUBLIC "src/include/")



add_executable("${SHARED_LIB_PROJECT}" ${sources})
target_link_libraries("${SHARED_LIB_PROJECT}" neq_max_seq_shared )
target_include_directories("${SHARED_LIB_PROJECT}" PUBLIC "src/include/")
message(STATUS "include & link")
