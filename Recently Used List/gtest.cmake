include(ExternalProject)

set(GTEST_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install/gtest)
set(GTEST_INCLUDE_DIR ${GTEST_INSTALL_DIR}/include)
set(GTEST_LIB_DIR ${GTEST_INSTALL_DIR}/lib)
ExternalProject_Add(EP-gtest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG release-1.8.0
	UPDATE_COMMAND ""
	CMAKE_ARGS 	-DCMAKE_CXX_FLAGS=/D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING 
				-DCMAKE_INSTALL_PREFIX:PATH=${GTEST_INSTALL_DIR}
				-Dgtest_force_shared_crt=ON)

add_library(gtest INTERFACE)
set_property(TARGET gtest PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIR})
set_property(TARGET gtest PROPERTY INTERFACE_LINK_LIBRARIES ${GTEST_LIB_DIR}/gtest.lib)
set_property(TARGET gtest APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${GTEST_LIB_DIR}/gmock.lib)

add_dependencies(gtest EP-gtest)
