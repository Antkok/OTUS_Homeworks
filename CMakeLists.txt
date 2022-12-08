cmake_minimum_required(VERSION 3.8)

# Setting name for this project.
set(PROJECT_NAME yamr)
set(PROJECT_DESCRIPTION "Library of bulk server")

# Adding a path with "cmake" modules to the system search paths.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Setting up a project version.
include(version)
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set(YAMR_PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif ()
set(YAMR_VERSION ${YAMR_MAJOR}.${YAMR_MINOR}.${YAMR_PATCH})
set(PROJECT_VERSION ${YAMR_MAJOR}.${YAMR_MINOR}.${YAMR_PATCH})
configure_file(version.h.in ${CMAKE_BINARY_DIR}/src/include/version.h @ONLY)

## Set property
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wextra -Wpedantic -g -O0)

# Setting up a project.
include(print)
include(function)

project(
  ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  DESCRIPTION ${PROJECT_DESCRIPTION}
  LANGUAGES CXX
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Boost COMPONENTS system program_options REQUIRED)

# Setting options on project
option(CLANG_FORMAT "Enable clang-format target" ON)
option(DOCUMENTATION "Build documentation" ON)
option(TESTING "Build tests" OFF)

if(CLANG_FORMAT)
  include(clang-format)
endif()

if(DOCUMENTATION)
  find_package(Doxygen COMPONENTS dot)
  include(doxygen)
endif()

# Settings for test cases.
if (TESTING)
  print("Target \"test\" enabled")
  include(gtest)
  # set GTEST_INCLUDE_DIR properly
  set(GTEST_INCLUDE_DIR
    ${CMAKE_SOURCE_DIR}/3rdpaty/gtest/src/googletest/include
    CACHE PATH "path to gtest includes"
  )
  include(CTest)
  include_directories(${GTEST_INCLUDE_DIR})
  add_subdirectory(test)
  enable_testing()
endif()

# Added directory
add_subdirectory(src)

# generate .deb package
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT john.jasper.doe@gmail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

set(CPACK_PACKAGE_VERSION_MAJOR "${YAMR_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${YAMR_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${YAMR_PATCH}")

# include will generate proper code for .deb generation
include(CPack)

