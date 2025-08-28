add_library(header only)
target_include_directories(type_data INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/bundle
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_data
)