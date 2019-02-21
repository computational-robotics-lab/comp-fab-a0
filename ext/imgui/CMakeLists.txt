cmake_minimum_required(VERSION 3.0)

# set name of the project
project(imgui CXX)

# add source files
file(GLOB sources 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)