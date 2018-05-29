cmake_minimum_required(VERSION 3.0)

project(RecentlyUsedList)

add_library(RecentLib recent.h recent.cpp)

add_executable(RecentApp app.cpp)
target_link_libraries(RecentApp RecentLib)

include(gtest.cmake)

add_executable(RecentTest test.cpp)
set_target_properties(RecentTest PROPERTIES OUTPUT_NAME "Recent.Tests"${CMAKE_RUNTIME_SUFFIX})
target_link_libraries(RecentTest RecentLib gtest)

enable_testing()
add_test(TEST RecentTest COMMAND $<TARGET_FILE:RecentTest>)
