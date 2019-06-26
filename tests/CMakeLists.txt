add_executable(storage_size_tests
  test.cpp
  fundamentals.cpp
)

set_target_properties(storage_size_tests PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS OFF
)

target_link_libraries(storage_size_tests PUBLIC storage_size)
