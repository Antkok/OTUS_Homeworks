cmake_minimum_required(VERSION 3.2)

option(CMAKE_ENABLE_DEBUG OFF)
option(CMAKE_ENABLE_TEST OFF)

set(BUILD_NUMBER 0)
if(NOT "$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")
    set(BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
endif(NOT "$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")

project(bulk_server VERSION 12.0.${BUILD_NUMBER})

set(
    CMAKE_VERBOSE_MAKEFILE TRUE
)

if(NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_PREFIX_PATH}/bin)
endif()

if(CMAKE_ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")
else()
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

configure_file(include/version.h.in ${CMAKE_PREFIX_PATH}/include/version.h)
file(GLOB_RECURSE SRC src/main.cpp
                      src/bulk_reader.cpp
                      src/async.cpp
                      src/async_server.cpp
                      src/async_session.cpp
)
file(GLOB_RECURSE H "include/*.h")

add_executable(${PROJECT_NAME} ${SRC} ${H})
target_link_libraries(${PROJECT_NAME} pthread)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_PREFIX_PATH}/include
)
link_directories(
    ${CMAKE_PREFIX_PATH}/lib
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# target test
if(CMAKE_ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

# target doc
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile)
    add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile)
else()
    message(STATUS "WARNING: doxygen not found - target \"doc\" will not be available")
endif()


#target package
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_DESCRIPTION "Otus C++ homework 12")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT a-zvg@ya.ru)
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_PREFIX_PATH}/dist")
include(CPack)
