find_package(GTest REQUIRED)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_PREFIX_PATH}/bin/test
)

add_executable(bulk_reader_test bulk_reader_test.cpp
    ../src/bulk_reader.cpp)
target_link_libraries(bulk_reader_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
add_test(NAME bulk_reader_test COMMAND bulk_reader_test)

add_executable(thread_test thread_test.cpp)
target_link_libraries(thread_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
add_test(NAME thread_test COMMAND thread_test)
