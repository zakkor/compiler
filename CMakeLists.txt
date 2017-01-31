cmake_minimum_required(VERSION 3.5)
project(Compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
  src/compiler.cpp
  src/parser.cpp
  src/lexer.cpp
  )

add_executable(Compiler ${SOURCE_FILES})

add_custom_command(TARGET Compiler POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/lang $<TARGET_FILE_DIR:Compiler>)
