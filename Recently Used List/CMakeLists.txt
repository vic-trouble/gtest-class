cmake_minimum_required(VERSION 3.0)

project(RecentlyUsedList)

add_library(RecentLib recent.h recent.cpp)

add_executable(RecentApp app.cpp)
target_link_libraries(RecentApp RecentLib)

include(gtest.cmake)

if(XCODE)
	add_library(RecentTest MODULE test.cpp GoogleTests.mm)
	set_target_properties(RecentTest PROPERTIES
		BUNDLE YES
		XCODE_PRODUCT_TYPE com.apple.product-type.bundle.unit-test)
	target_link_libraries(RecentTest "-framework XCTest")
else()
	add_executable(RecentTest test.cpp)
endif()

target_link_libraries(RecentTest RecentLib gtest)

enable_testing()
add_test(TEST RecentTest COMMAND $<TARGET_FILE:RecentTest>)
