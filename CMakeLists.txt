cmake_minimum_required(VERSION 3.30)

# have CMake export the commands we need to send to the compiler (things
# like include path and compiler switches). This writes the file
# compile_commands.json to the build folder where the c_cpp_properties.json
# file will refer to it and use it for vscode's intellisense
# compiler settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(aoc)

set(CXX_STANDARD 20)

# make sure vcpkg environment variables are set
if (NOT DEFINED ENV{VCPKG_ROOT} OR NOT DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
  message(NOTICE "The VCPKG_ROOT and VCPKG_DEFAULT_TRIPLET env vars must be defined")
  message(FATAL_ERROR "See https://learn.microsoft.com/en-us/vcpkg/ for documentation")
  endif()

# define a local variable for vcpkg_root directory
set(VCPKG_ROOT_DIR $ENV{VCPKG_ROOT})
message("${VCPKG_ROOT_DIR}")

# Tell CMake where to find vcpkg's CMake toolchain file
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")

# Add the DEBUG definition for debug builds, assures we can use
# the same define for debug builds across platforms
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(-DDEBUG)
endif()

file(GLOB_RECURSE source_files src/*.cpp)

add_executable(aoc ${source_files})

#-------- finding packages --------#
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

#-------- link libraries from packages --------#

target_link_libraries(aoc 
  PRIVATE fmt::fmt
  PRIVATE "${spdlog_LIBRARIES}") 

target_include_directories(
  aoc PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${spdlog_INCLUDE_DIRS}"
  )