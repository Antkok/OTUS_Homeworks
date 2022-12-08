cmake_minimum_required(VERSION 3.2)


if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(realty VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(realty VERSION 0.0.1)
endif ()

# Load settings for an external project.
find_package (Threads REQUIRED)
find_package (dlib REQUIRED)


# Copy a file to another location and modify its contents.
configure_file(version.h.in version.h)


add_executable(rclss rclss.cpp csvreader.cpp classifier.cpp datapreprocessor.cpp)
add_executable(rclst rclst.cpp csvreader.cpp classifier.cpp datapreprocessor.cpp)
# Add an executable to the project using the specified source files.


# Set propertiess to a target.
set_target_properties(rclss rclst PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Add include directories to a target.
# CMAKE_BINARY_DIR - The path to the top level of the build tree.
target_include_directories(rclss PRIVATE "${CMAKE_BINARY_DIR}")
target_include_directories(rclst PRIVATE "${CMAKE_BINARY_DIR}")

# Add include directories to the build.

target_link_libraries(rclss PRIVATE dlib )
target_link_libraries(rclst PRIVATE dlib )

# Add compile options to a target.
if (MSVC)
    target_compile_options(rclss PRIVATE
        /W4
    )
    target_compile_options(rclst PRIVATE
            /W4
            )
else ()    
    target_compile_options(rclss PRIVATE
        -Wall -Wextra  -pedantic -Werror
    )
    target_compile_options(rclst PRIVATE
            -Wall -Wextra  -pedantic -Werror
            )
endif()



# Load and run CMake code from a file or module.
install(TARGETS rclss RUNTIME DESTINATION bin)
install(TARGETS rclst RUNTIME DESTINATION bin)

# Set a CMake, cache or environment variable to a given value.
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT Antkok@ya.ru)

include(CPack)


