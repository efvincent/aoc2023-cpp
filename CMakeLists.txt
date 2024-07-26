cmake_minimum_required(VERSION 3.30)

project(aoc)

set(CXX_STANDARD 20)

option(USE_OPENGL "Enable or disable OpenGL dependency" OFF)

file(GLOB_RECURSE source_files src/*.cpp)

add_executable(aoc ${source_files})

# use of OpenGL is optional
IF(USE_OPENGL)
  
  set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")

  #-------- finding packages --------#
  find_package(glfw3 CONFIG REQUIRED)
  find_package(OpenGL REQUIRED)
  find_package(GLEW REQUIRED)
  find_package(GLUT REQUIRED)
  
  #-------- link libraries from packages --------#
  target_link_libraries(aoc PRIVATE
    glfw
    OpenGL::GL
    GLEW::GLEW
    GLUT::GLUT) 
ENDIF()


target_include_directories(aoc PUBLIC include)