project(cat3d)

file(GLOB examples "*.cpp")

foreach(example ${examples})
	get_filename_component(ex_out ${example} NAME_WE)
	add_executable(${ex_out} ${example})
	add_dependencies(${ex_out} cat3d)
	target_include_directories(${ex_out} PUBLIC
		"${CMAKE_SOURCE_DIR}/include"
	)
	target_link_libraries(${ex_out} cat3d)
endforeach()