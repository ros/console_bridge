include_directories (
  ${PROJECT_SOURCE_DIR}/test/gtest/include
  ${PROJECT_SOURCE_DIR}/test/gtest
  ${PROJECT_SOURCE_DIR}/test
)

link_directories(
  ${PROJECT_BINARY_DIR}/test
)


# Build gtest
add_library(gtest STATIC gtest/src/gtest-all.cc)
add_library(gtest_main STATIC gtest/src/gtest_main.cc)
target_link_libraries(gtest_main gtest)

execute_process(COMMAND cmake -E remove_directory ${CMAKE_BINARY_DIR}/test_results)
execute_process(COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/test_results)
include_directories(${GTEST_INCLUDE_DIRS})

set(tests
     console_TEST.cc)

if (MSVC)
  set_source_files_properties(console_TEST.cc PROPERTIES COMPILE_FLAGS
                                 /wd4996)
else()
  set_source_files_properties(console_TEST.cc PROPERTIES COMPILE_FLAGS
                                 -Wno-deprecated-declarations)
endif()

#################################################
# Build all the tests
foreach(GTEST_SOURCE_file ${tests})
  string(REGEX REPLACE ".cc" "" BINARY_NAME ${GTEST_SOURCE_file})
  add_executable(${BINARY_NAME} ${GTEST_SOURCE_file})

  add_dependencies(${BINARY_NAME}
      console_bridge
      gtest
      gtest_main)

  target_link_libraries(${BINARY_NAME}
     gtest_main
     gtest
     console_bridge)
  if (UNIX)
    target_link_libraries(${BINARY_NAME} pthread)
  endif()

   add_test(NAME    ${BINARY_NAME}
            COMMAND ${BINARY_NAME}
                    --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results/${BINARY_NAME}.xml)

   set_tests_properties(${BINARY_NAME} PROPERTIES TIMEOUT 240)
endforeach()
