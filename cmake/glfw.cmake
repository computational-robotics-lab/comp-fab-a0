set(GLFW_SRC_DIR ${CMAKE_SOURCE_DIR}/ext/glfw/include)
# file(GLOB sources ${GLFW_SRC_DIR}/*.h ${GLFW_SRC_DIR}/*.c)
# add_library(glfw ${sources})
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/glfw)
