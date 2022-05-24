cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER}) 
    project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(print_ip VERSION 0.0.3)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package (Threads REQUIRED)

configure_file(version.h.in "${CMAKE_CURRENT_SOURCE_DIR}/version.h")

#add_subdirectory(
#       "${CMAKE_CURRENT_SOURCE_DIR}/gtest"
#       googletest
#)

add_executable(print_ip main.cpp)
add_library(print_ip.lib STATIC lib.cpp)
add_executable(test_boost testboost.cpp)
#add_executable(test_google testg.cpp)

set_target_properties(print_ip  print_ip.lib test_google PROPERTIES #test_boost
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(print_ip.lib
    PUBLIC "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_boost PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(print_ip
    print_ip.lib
)

target_link_libraries(test_boost
    ${Boost_LIBRARIES}
)

#target_link_libraries(test_google
#    gtest
#    ${CMAKE_THREAD_LIBS_INIT}
#)

if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
    target_compile_options(print_ip.lib PRIVATE
        /W4
    )
    target_compile_options(test_boost PRIVATE
        /W4
    )
    #target_compile_options(test_google PRIVATE
    #    /W4
    #)
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(print_ip.lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_boost PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    #target_compile_options(test_google PRIVATE
    #    -Wall -Wextra -pedantic -Werror
    #)
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT Antkok@yandex.ru)

include(CPack)
enable_testing()

add_test(test_valid_version print_ip)
#add_test(GOOGLE_TEST2 print_ip)
#add_test(GOOGLE_TEST3 print_ip)
#add_test(GOOGLE_TEST4 print_ip)
#add_test(GOOGLE_TEST5 print_ip)
#add_test(GOOGLE_TEST6 print_ip)
#add_test(GOOGLE_TEST7 print_ip)
#add_test(GOOGLE_TEST8 print_ip)