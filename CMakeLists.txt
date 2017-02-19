cmake_minimum_required(VERSION 3.5)
project(Compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
  src/compiler.cpp
  src/parser.cpp
  src/lexer.cpp
  src/token.cpp
  src/test.cpp
  src/astnode.cpp
  src/typenode.cpp
  src/symbol.cpp
  src/varnode.cpp
  src/argnode.cpp
  src/numlitnode.cpp
  src/binaryops.cpp
  src/inferdeclnode.cpp
  src/seqnode.cpp
  src/ifnode.cpp
  src/assignnode.cpp
  src/funcdeclnode.cpp
  src/retnode.cpp
  src/unaryops.cpp
  src/declnode.cpp
  src/structdeclnode.cpp
  )

add_executable(Compiler ${SOURCE_FILES})

add_custom_command(TARGET Compiler POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/lang $<TARGET_FILE_DIR:Compiler>)

add_custom_command(TARGET Compiler POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/tests $<TARGET_FILE_DIR:Compiler>)
