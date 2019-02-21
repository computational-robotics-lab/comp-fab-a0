project(gl3w C)

find_package(OpenGL REQUIRED)

add_library(gl3w STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/GL/gl3w.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/GL/gl3w.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/GL/glcorearb.h
)

target_include_directories(gl3w PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(gl3w 
	${OPENGL_LIBRARIES} 
	${CMAKE_DL_LIBS}
)