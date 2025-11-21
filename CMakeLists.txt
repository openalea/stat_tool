# Initialize the CMake project
cmake_minimum_required(VERSION 3.20)

##################################################
# If we are running in a Conda environment, we automatically
# add the Conda env prefix to the CMAKE_PREFIX_PATH

if(DEFINED ENV{CONDA_PREFIX})
  list(APPEND CMAKE_PREFIX_PATH "$ENV{CONDA_PREFIX}")
  #TODO: Windows Conda environments are structured differently,
  #      how unfortunate is this?
  list(APPEND CMAKE_PREFIX_PATH "$ENV{CONDA_PREFIX}/Library")
endif()

if (DEFINED ENV{CONDA_PREFIX})
    # Anaconda Environment
    message(STATUS "Anaconda environment detected: " $ENV{CONDA_PREFIX})

    set(CMAKE_INCLUDE_PATH "$ENV{CONDA_PREFIX}/include" ${CMAKE_INCLUDE_PATH})
    set(CMAKE_LIBRARY_PATH "$ENV{CONDA_PREFIX}/lib" ${CMAKE_LIBRARY_PATH})

    if (DEFINED ENV{PREFIX})
        file(TO_CMAKE_PATH $ENV{PREFIX} TMP_CONDA_ENV)
    else()
        file(TO_CMAKE_PATH $ENV{CONDA_PREFIX} TMP_CONDA_ENV)
    endif()

    if (WIN32)
        set(CONDA_ENV "${TMP_CONDA_ENV}/Library/")
    else()
        set(CONDA_ENV "${TMP_CONDA_ENV}/")
    endif()

    set(CONDA_PYTHON_ENV "${TMP_CONDA_ENV}/")

    set(USE_CONDA ON)

else()
    message(STATUS "Compilation outside an anaconda environment.")
    set(USE_CONDA OFF)
endif()

if (DEFINED ENV{CONDA_BUILD})
    message(STATUS "Conda build detected. " $ENV{CONDA_BUILD})

    if (WIN32)
        set(Python_ROOT_DIR "${PREFIX}")
    endif()

    # specify the cross compiler
    set(CMAKE_C_COMPILER $ENV{CC})
    set(CMAKE_LINKER $ENV{LD})
    set(CMAKE_AR $ENV{AR})
    set(CMAKE_NM $ENV{NM})
    set(CMAKE_RANLIB $ENV{RANLIB})
    set(CMAKE_STRIP $ENV{STRIP})
    set(CMAKE_INSTALL_NAME_TOOL $ENV{INSTALL_NAME_TOOL})

    if (APPLE)
        set(CMAKE_OSX_ARCHITECTURES $ENV{OSX_ARCH})
    endif()

    set(CMAKE_CXX_COMPILER $ENV{CXX})
    set(CMAKE_CXX_COMPILER_RANLIB $ENV{RANLIB})
    set(CMAKE_CXX_COMPILER_AR $ENV{AR})

    # where is the target environment
    set(CMAKE_FIND_ROOT_PATH $ENV{PREFIX} $ENV{BUILD_PREFIX})
    if (APPLE)
        list(APPEND CMAKE_FIND_ROOT_PATH $ENV{CONDA_BUILD_SYSROOT} )
    endif()
    if (WIN32)
        list(APPEND CMAKE_FIND_ROOT_PATH $ENV{BUILD_PREFIX}/Library/usr $ENV{PREFIX}/Library/usr)
        set(CMAKE_INCLUDE_PATH "$ENV{BUILD_PREFIX}/Library/usr/include" ${CMAKE_INCLUDE_PATH})
        set(CMAKE_LIBRARY_PATH "$ENV{BUILD_PREFIX}/Library/usr/lib" ${CMAKE_LIBRARY_PATH})
    endif()
    if (UNIX)
        # I add both old stype and new style cdts : https://github.com/conda-forge/cdt-builds#old-stylelegacy-vs-new-style-cdts
        list(APPEND CMAKE_FIND_ROOT_PATH $ENV{BUILD_PREFIX}/x86_64-conda-linux-gnu/sysroot $ENV{BUILD_PREFIX}/$ENV{HOST}/sysroot )
        list(APPEND CMAKE_FIND_ROOT_PATH $ENV{PREFIX}/x86_64-conda-linux-gnu/sysroot $ENV{PREFIX}/$ENV{HOST}/sysroot )

        link_directories($ENV{BUILD_PREFIX}/x86_64-conda-linux-gnu/sysroot/lib64 $ENV{BUILD_PREFIX}/$ENV{HOST}/sysroot/lib64)
        link_directories($ENV{BUILD_PREFIX}/x86_64-conda-linux-gnu/sysroot/lib $ENV{BUILD_PREFIX}/$ENV{HOST}/sysroot/lib)
        link_directories($ENV{BUILD_PREFIX}/x86_64-conda-linux-gnu/sysroot/usr/lib64 $ENV{BUILD_PREFIX}/$ENV{HOST}/sysroot/usr/lib64)
        link_directories($ENV{BUILD_PREFIX}/x86_64-conda-linux-gnu/sysroot/usr/lib $ENV{BUILD_PREFIX}/$ENV{HOST}/sysroot/usr/lib)
    endif()

    message(STATUS "CMAKE_FIND_ROOT_PATH :")
    foreach(dir ${CMAKE_FIND_ROOT_PATH})
        message(STATUS " - " ${dir})
    endforeach()

    # search for programs in the build host directories
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
    # for libraries and headers in the target directories
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


    set(USE_CONDA_BUILD ON)
else()
    set(USE_CONDA_BUILD OFF)
endif()

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
if(USE_CONDA_BUILD)
    set(CMAKE_INSTALL_PREFIX $ENV{PREFIX} CACHE PATH "..." FORCE)
else()
    set(CMAKE_INSTALL_PREFIX ${CONDA_ENV} CACHE PATH "..." FORCE)
endif()
message(STATUS "Default install prefix to " ${CMAKE_INSTALL_PREFIX})
endif()

##################################################
# Define the version

if(SKBUILD)
  set(STAT_TOOL_VERSION ${SKBUILD_PROJECT_VERSION})
else()
  set(STAT_TOOL_VERSION "2.0.0")
endif()

project(openalea.stat_tool
  VERSION ${STAT_TOOL_VERSION}
  LANGUAGES CXX
  DESCRIPTION "OpenAlea Stat Tool library for structure analysis")

##################################################
# Set CMake policies for this project

# We allow <Package>_ROOT (env) variables for locating dependencies using find_paclage
cmake_policy(SET CMP0074 NEW)
# We allow target_sources to convert relative paths to absolute paths
cmake_policy(SET CMP0076 NEW)
 # for Python*_FIND_STRATEGY=LOCATION
cmake_policy(SET CMP0094 NEW)

##################################################
# Initialize some default paths
# See https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)

##################################################
# Set C++ standard and compile options

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# This may be set in pyproject.toml
set(CMAKE_VERBOSE_MAKEFILE ON)

##################################################
# For Python bindings, we need to enable position-independent code
set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # For shared libs

##################################################
# TODO : REMOVE?
# if(WIN32)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -enable-stdcall-fixup -enable-auto-import -enable-runtime-pseudo-reloc -s")
# endif()


# if(DEFINED ENV{SKIP_BUILD})
#   message(STATUS "Skipping build of C/C++ extensions")
#   return()  # stops processing the CMakeLists here
# endif()

# RPath settings
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(
  FIND
  CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES
  ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
  isSystemDir
)
if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
endif("${isSystemDir}" STREQUAL "-1")



if (MSVC)
    string(REGEX REPLACE "/W3" "/W0" ${CMAKE_CXX_FLAGS} "${${CMAKE_CXX_FLAGS}}") 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")

    # To fix compilation error with vc14 and boost
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DHAVE_SNPRINTF")
endif()

# Options
option(WITH_EFENCE "Build with efence library" OFF)
option(WITH_TEST "Build tests" OFF)

##################################################
# Add a library for stat_tool and its Python wrappers
add_library(oastat_tool SHARED)

##################################################
# Find external dependencies
find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
find_package(Boost REQUIRED COMPONENTS python)

##################################################
# Setup lib, inc, defines for C++ oastat_tool lib

target_include_directories(oastat_tool
  PUBLIC
    ${Boost_INCLUDE_DIRS}
)

# Export symbols on Windows
if (WIN32 OR MSVC)
  target_compile_definitions(oastat_tool PUBLIC STAT_TOOL_MAKEDLL)
endif()

# Optionally add efence
if(WITH_EFENCE)
  target_compile_definitions(oastat_tool PUBLIC DEBUG)
  target_link_libraries(oastat_tool PUBLIC efence)
endif()

# Add files to build
add_subdirectory(src/cpp/stat_tool)


##################################################
# Add a Python binding library 
python_add_library(_stat_tool MODULE)

target_include_directories(oastat_tool
  PUBLIC
    "src/cpp"
)

target_link_libraries(_stat_tool
  PRIVATE
    oastat_tool
    Boost::python
    Python::Module
  )

  target_compile_definitions(_stat_tool PRIVATE BOOST_ALL_NO_LIB)

  # Control the output name of the produced shared library
  set_target_properties(_stat_tool PROPERTIES PREFIX "")
  set_target_properties(_stat_tool PROPERTIES OUTPUT_NAME "_stat_tool")
  if(WIN32)
    set_target_properties(_stat_tool PROPERTIES SUFFIX ".pyd")
  elseif(APPLE)
    set_target_properties(_stat_tool PROPERTIES SUFFIX ".so")
  endif()

add_subdirectory("src/wrapper/")


if(APPLE)
    set_target_properties(_stat_tool PROPERTIES INSTALL_RPATH "@loader_path/.")
elseif(UNIX)
    set_target_properties(_stat_tool PROPERTIES INSTALL_RPATH "$ORIGIN/.")
endif()

##################################################
# Install targets and headers for stat_tool lib
install(TARGETS oastat_tool
            RUNTIME DESTINATION "${CONDA_ENV}bin/"
            LIBRARY DESTINATION "${CONDA_ENV}lib/"
            ARCHIVE DESTINATION "${CONDA_ENV}lib/"
)

# Install header
install(TARGETS oastat_tool
        PUBLIC_HEADER
          DESTINATION "${CONDA_ENV}include/stat_tool"
)

install(
  TARGETS
    _stat_tool
  DESTINATION "${SKBUILD_PLATLIB_DIR}/openalea/stat_tool"
)

# Optionally handle tests
# TODO TO TEST
if(WITH_TEST)
  enable_testing()
  add_subdirectory(test/cpp)
endif()

