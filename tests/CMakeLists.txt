file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.cpp")

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/tests/main.cpp")

foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests" ${sources} ${file} "${PROJECT_SOURCE_DIR}/tests/main.cpp")
  target_link_libraries("${name}_tests" gtest_main)
  target_include_directories("${name}_tests" PUBLIC ${PROJECT_SOURCE_DIR}/src/include)
  add_test(NAME ${name} COMMAND "${name}_tests")
 
endforeach()