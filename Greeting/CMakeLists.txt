cmake_minimum_required(VERSION 3.0)

project(Greet)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

add_library(GreetLib greet.h greet.cpp)

add_executable(GreetApp app.cpp)
target_link_libraries(GreetApp GreetLib)

include(gtest.cmake)

if(XCODE)
	option(USE_XCTEST "Integrate tests with Xcode" ON)
	if(USE_XCTEST)
		add_library(GreetTest MODULE test.cpp GoogleTests.mm)
		set_target_properties(GreetTest PROPERTIES
			BUNDLE YES
			XCODE_PRODUCT_TYPE com.apple.product-type.bundle.unit-test)
		target_link_libraries(GreetTest "-framework XCTest")
	else()
		add_executable(GreetTest test.cpp)
	endif()
else()
	add_executable(GreetTest test.cpp)
endif()

target_link_libraries(GreetTest GreetLib gtest)

enable_testing()
add_test(TEST GreetTest COMMAND $<TARGET_FILE:GreetTest>)
