set(NANOVG_SRC_DIR ${CMAKE_SOURCE_DIR}/ext/nanovg/src)
file(GLOB sources ${NANOVG_SRC_DIR}/*.h ${NANOVG_SRC_DIR}/*.c)
add_library(nanovg ${sources})
set(NANOVG_SRC_DIR ${NANOVG_SRC_DIR} PARENT_SCOPE)
