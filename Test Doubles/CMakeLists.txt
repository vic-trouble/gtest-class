cmake_minimum_required(VERSION 3.0)

project(Doubles)

add_library(DoublesLib doubles.h doubles.cpp)

include(gtest.cmake)

if(XCODE)
	option(USE_XCTEST "Integrate tests with Xcode" ON)
	if(USE_XCTEST)
		add_library(DoublesTest MODULE test.cpp GoogleTests.mm)
		set_target_properties(DoublesTest PROPERTIES
			BUNDLE YES
			XCODE_PRODUCT_TYPE com.apple.product-type.bundle.unit-test)
		target_link_libraries(DoublesTest "-framework XCTest")
	else()
		add_executable(DoublesTest test.cpp)
	endif()
else()
	add_executable(DoublesTest test.cpp)
endif()

target_link_libraries(DoublesTest DoublesLib gtest)

enable_testing()
add_test(TEST DoublesTest COMMAND $<TARGET_FILE:DoublesTest>)
