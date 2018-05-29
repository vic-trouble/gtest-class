cmake_minimum_required(VERSION 3.0)

project(LeapYear)

add_library(LeapLib leap.h leap.cpp)

add_executable(LeapApp app.cpp)
target_link_libraries(LeapApp LeapLib)

include(gtest.cmake)

if(XCODE)
	option(USE_XCTEST "Integrate tests with Xcode" ON)
	if(USE_XCTEST)
		add_library(LeapTest MODULE test.cpp GoogleTests.mm)
		set_target_properties(LeapTest PROPERTIES
			BUNDLE YES
			XCODE_PRODUCT_TYPE com.apple.product-type.bundle.unit-test)
		target_link_libraries(LeapTest "-framework XCTest")
	else()
		add_executable(LeapTest test.cpp)
	endif()
else()
	add_executable(LeapTest test.cpp)
endif()

target_link_libraries(LeapTest LeapLib gtest)

enable_testing()
add_test(TEST LeapTest COMMAND $<TARGET_FILE:LeapTest>)
