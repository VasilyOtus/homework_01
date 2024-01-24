cmake_minimum_required(VERSION 3.0.2)

set(PATCH_VERSION "1" CACHE STRING "Patch version")

project(helloworld VERSION 0.0.${PATCH_VERSION})

find_package(GTest REQUIRED)

set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADERS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADERS_DST_DIR ${CMAKE_CURRENT_BINARY_DIR}/include)

set(LIB_NAME ${PROJECT_NAME})
set(CLI_NAME ${PROJECT_NAME}-cli)
set(TEST_NAME ${PROJECT_NAME}-test)

configure_file(${HEADERS_SRC_DIR}/version.h.in ${HEADERS_DST_DIR}/version.h @ONLY)

# Build
add_library(${LIB_NAME} ${SOURCES_DIR}/lib.cpp)
add_executable(${CLI_NAME} ${SOURCES_DIR}/cli.cpp)
add_executable(${TEST_NAME} ${SOURCES_DIR}/test.cpp)

# Properties
set_target_properties(${LIB_NAME} ${CLI_NAME} ${TEST_NAME}
	PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(${LIB_NAME}
	PRIVATE ${HEADERS_SRC_DIR} ${HEADERS_DST_DIR}
)
target_include_directories(${CLI_NAME}
	PRIVATE ${HEADERS_SRC_DIR} ${HEADERS_DST_DIR}
)
target_include_directories(${TEST_NAME}
	PRIVATE ${HEADERS_SRC_DIR} ${HEADERS_DST_DIR} ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(${CLI_NAME}
	PRIVATE ${LIB_NAME}
)
target_link_libraries(${TEST_NAME}
	PRIVATE ${LIB_NAME} ${GTEST_BOTH_LIBRARIES}
)

if (MSVC)
	target_compile_options(${LIB_NAME}
		PRIVATE /W4
	)
	target_compile_options(${CLI_NAME}
		PRIVATE /W4
	)
	target_compile_options(${TEST_NAME}
		PRIVATE /W4
	)
else ()
	target_compile_options(${LIB_NAME}
		PRIVATE -Wall -Wextra -pedantic -Werror
	)
	target_compile_options(${CLI_NAME}
		PRIVATE -Wall -Wextra -pedantic -Werror
	)
	target_compile_options(${TEST_NAME}
		PRIVATE -Wall -Wextra -pedantic -Werror
	)
endif()

# Install
include(GNUInstallDirs)

install(TARGETS ${LIB_NAME} ${CLI_NAME}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Deb package
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

# Tests
enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
