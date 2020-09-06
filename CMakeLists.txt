cmake_minimum_required(VERSION 3.13)
project(cat3d)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# for dev use
if(BUILD_SANDBOX)
	add_subdirectory(sandbox/)
endif()

# build the examples
option(BUILD_EXAMPLES "Build the example programs" OFF)
if(BUILD_EXAMPLES)
	add_subdirectory(examples/)
endif()

option(BUILD_TESTS "Build the unit tests" OFF)
if(BUILD_TESTS)
	add_subdirectory(tests/)
	enable_testing()
endif()

file(GLOB_RECURSE sources "src/*.cpp")

add_library(cat3d ${sources})
target_include_directories(cat3d PUBLIC
	"include/"
	"lib/"
)
target_compile_options(cat3d PUBLIC -Wall -Wno-unused-variable)
target_link_libraries(cat3d
	glfw
	GLEW
	GL
)

add_test(NAME UnitTests COMMAND cat3d_test)
