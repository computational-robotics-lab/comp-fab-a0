cmake_minimum_required(VERSION 3.5)

find_package(Json REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(guiLib
    ${sources}
)
target_link_libraries(guiLib
    ${OPENGL_LIBRARIES} # open gl libs already linked by gl3w, linking again ...
    gl3w
    glfw
    imgui
    nanovg
)
target_include_directories(guiLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${NANOVG_SRC_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/glfw/include
)

# if(WIN32)
#     # copy dxl dll to binary dir
#     add_custom_command(
#             TARGET example_motor_group_gui POST_BUILD
#             COMMAND ${CMAKE_COMMAND} -E copy
#                     ${DynamixelSDK_DLLS}
#                     ${CMAKE_CURRENT_BINARY_DIR}
#     )
# endif(WIN32)
