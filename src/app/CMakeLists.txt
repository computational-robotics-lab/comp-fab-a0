cmake_minimum_required(VERSION 3.5)

project(app)

find_package(Json REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME}
    guiLib
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
