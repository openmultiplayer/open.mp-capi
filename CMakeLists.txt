cmake_minimum_required(VERSION 3.10)
project(OMP-CAPI VERSION 1.0.0 LANGUAGES C)

add_library(OMP-CAPI INTERFACE)
target_include_directories(OMP-CAPI INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
