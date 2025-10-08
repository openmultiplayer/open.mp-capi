cmake_minimum_required(VERSION 3.10)
project(OMP-CAPI LANGUAGES C DESCRIPTION "C-API SDK for to call open.mp exposed API functions or create components with" VERSION 1)

add_library(OMP-CAPI INTERFACE)
target_include_directories(OMP-CAPI INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE omp_capi_source_list "*.h")

set_property(TARGET OMP-CAPI PROPERTY SOURCES ${omp_capi_source_list})
