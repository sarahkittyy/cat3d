project(cat3d)

file(GLOB_RECURSE sources "*.cpp")

add_executable(cat3d_test ${sources})
add_dependencies(cat3d_test cat3d)
target_include_directories(cat3d_test PUBLIC
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/lib/catch2"
)
target_link_libraries(cat3d_test cat3d)