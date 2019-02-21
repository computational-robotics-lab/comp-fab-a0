cmake_minimum_required(VERSION 3.5)

# set name of the project
project(assignement0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)

# thirdparty code
add_subdirectory(ext)

# our code
add_subdirectory(src)
