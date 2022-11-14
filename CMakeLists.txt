cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER}) 
    project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(matrix VERSION 0.0.3)
endif()

find_package (Threads REQUIRED)

configure_file(version.h.in "${CMAKE_CURRENT_SOURCE_DIR}/version.h")

add_subdirectory(
       "${CMAKE_CURRENT_SOURCE_DIR}/gtest"
       googletest
)

add_executable(matrix main.cpp matrix.cpp)
add_library(matrix.lib STATIC lib.cpp)
add_executable(test_google test.cpp)

set_target_properties(matrix matrix.lib test_google PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(matrix.lib
    PUBLIC "${CMAKE_BINARY_DIR}"
)

target_link_libraries(matrix
    matrix.lib
)

target_link_libraries(test_google
    gtest
    ${CMAKE_THREAD_LIBS_INIT}
)

if (MSVC)
    target_compile_options(matrix PRIVATE
        /W4
    )
    target_compile_options(matrix.lib PRIVATE
        /W4
    )
    target_compile_options(test_google PRIVATE
        /W4
    )
else ()
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(matrix.lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_google PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT lismut@gmail.com)

include(CPack)
enable_testing()

add_test(GOOGLE_TEST1 matrix)
add_test(GOOGLE_TEST2 matrix)
add_test(GOOGLE_TEST3 matrix)
