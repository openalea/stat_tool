# Glob includes and sources
file(GLOB HEADERS "*.h" "*.hpp")
file(GLOB SOURCES "*.cpp")

add_library(stat_tool SHARED ${SOURCES})

# Export symbols on Windows
if (WIN32)
    target_compile_definitions(stat_tool PRIVATE STAT_TOOL_MAKEDLL)
endif()

# Optionally add efence
if(WITH_EFENCE)
  target_compile_definitions(stat_tool PRIVATE DEBUG)
  target_link_libraries(stat_tool PRIVATE efence)
endif()

target_include_directories(stat_tool PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(stat_tool
    PUBLIC ${Boost_LIBRARIES} 
)
target_link_libraries(stat_tool
    PUBLIC Python3::Python
)


set(STAT_TOOL_LIBDIR "${SKBUILD_PLATLIB_DIR}/openalea/stat_tool")

message(STATUS "Installing stat_tool to ${STAT_TOOL_LIBDIR}")
install(TARGETS stat_tool
  LIBRARY DESTINATION "${STAT_TOOL_LIBDIR}"
)

message(STATUS "Installing headers: ${HEADERS}")
message(STATUS "Installing headers to ${SKBUILD_HEADERS_DIR}/stat_tool")
install(FILES ${HEADERS}
  DESTINATION "${SKBUILD_HEADERS_DIR}/stat_tool"
)
