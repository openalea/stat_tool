if(NOT WITH_TEST)
  return()
endif()

# List all test files
file(GLOB TEST_FILES "*.cpp")

# Loop over test files and create one executable per file
foreach(test_src ${TEST_FILES})
  # Remove the .cpp extension for the target name
  get_filename_component(TEST_NAME ${test_src} NAME_WE)

  add_executable(${TEST_NAME} ${test_src})

  # Link with your main library and GoogleTest (if used)
  target_link_libraries(${TEST_NAME} PRIVATE oastat_tool)

  # Register the test with CTest
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

