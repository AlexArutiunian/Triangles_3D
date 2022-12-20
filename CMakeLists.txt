cmake_minimum_required(VERSION 3.11)

project(triangle)

list(APPEND bin triangle)
list(APPEND cpp triang.cpp)

foreach(build IN ZIP_LISTS bin cpp)
	add_executable(${build_0} ${build_1})
    
	set_target_properties(
		${build_0} PROPERTIES
		CXX_STANDART 20
		CXX_STANDART_REQUIRED ON
	)

endforeach()
