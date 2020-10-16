cmake_minimum_required(VERSION 3.12.4)
set(STATIC_LIB_PORJECT with_static)
set(SHARED_LIB_PORJECT with_shared)

project("${STATIC_LIB_PORJECT}")
project("${SHARED_LIB_PORJECT}")

##
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
add_subdirectory(./tests)



if ("${TARGET_CPU}" STREQUAL "amd64")
    set (CMAKE_SIZEOF_VOID_P 8)

    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)
    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS FALSE)
elseif ("${TARGET_CPU}" STREQUAL "x86")
    set (CMAKE_SIZEOF_VOID_P 4)

    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)
    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS TRUE)

    if (GCC)
        add_compile_options(-Wall -Werror -Wpedantic)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
        set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32")
    endif ()
else ()
    message (FATAL_ERROR "Unsupported CPU: ${TARGET_CPU}")
endif()

file(GLOB sources "src/*.cpp")
add_executable(${STATIC_LIB_PORJECT} ${sources})

add_executable(${SHARED_LIB_PORJECT} ${sources})


