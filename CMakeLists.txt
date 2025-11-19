cmake_minimum_required(VERSION 3.20)

if(DEFINED SKBUILD_PROJECT_NAME AND DEFINED SKBUILD_PROJECT_VERSION)
  project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    DESCRIPTION "Statistical tools for OpenAlea"
    LANGUAGES CXX)
  message(STATUS "Building project version: ${SKBUILD_PROJECT_VERSION}")
else()
  project(stat_tool LANGUAGES CXX)
endif()

include(GNUInstallDirs)

# Set C++ standard and compile options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
# set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # For shared libs

if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -enable-stdcall-fixup -enable-auto-import -enable-runtime-pseudo-reloc -s")
endif()

if(DEFINED ENV{SKIP_BUILD})
  message(STATUS "Skipping build of C/C++ extensions")
  return()  # stops processing the CMakeLists here
endif()

if (MSVC)
    string(REGEX REPLACE "/W3" "/W0" ${CMAKE_CXX_FLAGS} "${${CMAKE_CXX_FLAGS}}") 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")

    # To fix compilation error with vc14 and boost
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DHAVE_SNPRINTF")
endif()

# Options
option(WITH_EFENCE "Build with efence library" OFF)
option(WITH_TEST "Build tests" OFF)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
message(STATUS "Python LIB : " ${Python_LIBRARIES})
include_directories(${Python_INCLUDE_DIRS})

include(cmake/wrapper.cmake)

set(boost_python python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR})
find_package(Boost REQUIRED COMPONENTS ${boost_python})

add_subdirectory("src/cpp/stat_tool")
add_subdirectory("src/wrapper/")

# Optionally handle tests
if(WITH_TEST)
  enable_testing()
  add_subdirectory(test/cpp)
endif()

