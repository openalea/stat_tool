# Glob includes and sources
file(GLOB HEADERS "*.h" "*.hpp")
file(GLOB SOURCES "*.cpp")


target_include_directories(oastat_tool PUBLIC .)

target_sources(
  oastat_tool
  PRIVATE
    ${SOURCES}
)

# Add the headers to be installed with the library
set_target_properties(oastat_tool PROPERTIES PUBLIC_HEADER ${HEADERS})

