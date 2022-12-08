cmake_minimum_required (VERSION 3.8)

project ("Otus_11" VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 
#dispatcher block

set(CMD_SRC            "lib/dispatcher/command/icommand.h" 
                       "lib/dispatcher/command/simple_command.h")
set(LOG_SRC            "lib/dispatcher/logger/logger.h" 
                       "lib/dispatcher/logger/logger_screen.h" 
                       "lib/dispatcher/logger/logger_file.h")
set(CONCURRENT_SRC     "lib/dispatcher/concurrent/concurrent_deque.h")
set(DISPATCHER_SRC     "lib/dispatcher/dispatcher.h" ${CONCURRENT_SRC} ${LOG_SRC} ${CMD_SRC})   
#\dispatcher block

set(ASYNC_LIB_SRC "lib/bulk_async.h" "lib/bulk_async.cpp" ${DISPATCHER_SRC})

add_library(libasync_static STATIC ${ASYNC_LIB_SRC})
add_library(libasync SHARED ${ASYNC_LIB_SRC})

set_target_properties (
	libasync
	libasync_static
	PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	OUTPUT_NAME async
)

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()


Find_package(Threads)

target_link_libraries( libasync_static ${CMAKE_THREAD_LIBS_INIT}  $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)
target_link_libraries( libasync ${CMAKE_THREAD_LIBS_INIT}  $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)


target_include_directories(
	libasync_static
	PRIVATE
	${PROJECT_SOURCE_DIR}/lib/dispatcher
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

target_include_directories(
	libasync
	PRIVATE
	${PROJECT_SOURCE_DIR}/lib/dispatcher
	${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

##################################
#######USAGE_EXAMPLE_BLOCK########
add_executable(bulk_async_test "test/main.cpp" ) 

set_target_properties (
	bulk_async_test PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_include_directories(			
	bulk_async_test
	PRIVATE
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/lib/dispatcher
)

target_link_libraries(bulk_async_test ${CMAKE_THREAD_LIBS_INIT} libasync_static $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)


##################################
###########TEST_BLOCK#############
find_package(GTest REQUIRED)

if(NOT GTEST_FOUND )
	message(SEND_ERROR "Failed to find GTest")
	return()
endif()

add_executable(gtest_bulk_async "test/gtest_bulk_async.cpp" ) 

set_target_properties (
	gtest_bulk_async  PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON	
)

target_include_directories(			
	gtest_bulk_async 
	PRIVATE
	${GTEST_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/lib/dispatcher
)

target_link_libraries(gtest_bulk_async 
	${GTEST_BOTH_LIBRARIES} 
	${CMAKE_THREAD_LIBS_INIT}  
	libasync_static
	$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

# Copy output
file(COPY ${PROJECT_SOURCE_DIR}/lib/bulk_async.h DESTINATION ${CMAKE_BINARY_DIR}/Otus_11)

#CMAKE_CURRENT_BINARY_DIR
enable_testing()
add_test(gtest_bulk_async gtest_bulk_async)
##############################################
###################INSTALL####################
install(TARGETS libasync  DESTINATION bin/lib/)	   
install(TARGETS libasync_static  DESTINATION bin/lib/)
install(FILES ${PROJECT_SOURCE_DIR}/lib/bulk_async.h DESTINATION bin/lib/)

set(CPACK_PACKAGE_NAME "OtusHomeworks")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Karyukov")
set(CPACK_PACKAGE_CONTACT "pavelkaryukov@gmail.com")
include (CPack)