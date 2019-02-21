# - Try to find the JSON library
# Once done this will define
#
#  JSON_FOUND - system has JSON
#  JSON_INCLUDE_DIR - **the** JSON include directory
if(JSON_FOUND)
    return()
endif()

find_path(JSON_INCLUDE_DIR json.hpp
    HINTS
        ENV JSON_DIR
    PATHS
        ${CMAKE_SOURCE_DIR}/ext/json
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JSON
    "\nJSON not found --- You can download it here: https://raw.githubusercontent.com/nlohmann/json"
    JSON_INCLUDE_DIR)
mark_as_advanced(JSON_INCLUDE_DIR)
