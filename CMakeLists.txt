cmake_minimum_required(VERSION 3.10)
project(storage_size)

set(header_files
  ${CMAKE_CURRENT_SOURCE_DIR}/include/storage_size/size.h
)

add_library(storage_size INTERFACE)

target_sources(storage_size INTERFACE "$<BUILD_INTERFACE:${header_files}>")
target_include_directories(storage_size INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)
target_include_directories(storage_size SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

install(DIRECTORY include/storage_size DESTINATION include)

option(STORAGE_SIZE_BUILD_TESTS "build tests" OFF)
if(${STORAGE_SIZE_BUILD_TESTS})
  add_subdirectory(tests)
endif()
