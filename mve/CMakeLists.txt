cmake_minimum_required(VERSION 3.10)

project(MVE)

add_definitions(-DMVE_NO_TIFF_SUPPORT)
add_definitions(-DMVE_NO_JPEG_SUPPORT)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall  -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -O3")

# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   add_definitions(-DCOMPILEDWITHC11)
   message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
   add_definitions(-DCOMPILEDWITHC0X)
   message(STATUS "Using flag -std=c++0x.")
else()
   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Point to the directory where libpng is installed or built
# set(PNG_LIBRARY /opt/homebrew/Cellar/libpng/1.6.40/lib)
# set(PNG_PNG_INCLUDE_DIR /opt/homebrew/Cellar/libpng/1.6.40/include)
# find_package(PNG REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/math)
include_directories(${CMAKE_SOURCE_DIR}/mve)
include_directories(${CMAKE_SOURCE_DIR}/acc)
include_directories(${CMAKE_SOURCE_DIR}/util)

file (GLOB HEADERS
     "${CMAKE_SOURCE_DIR}/math/*.h"
     "${CMAKE_SOURCE_DIR}/acc/*.h"
     "${CMAKE_SOURCE_DIR}/util/*.h"
     "${CMAKE_SOURCE_DIR}/mve/*.h"
     )

file(GLOB MVE_SOURCES
     "${CMAKE_SOURCE_DIR}/math/[^_]*.cc"
     "${CMAKE_SOURCE_DIR}/acc/[^_]*.cc"
     "${CMAKE_SOURCE_DIR}/util/[^_]*.cc"
     "${CMAKE_SOURCE_DIR}/mve/[^_]*.cc")

add_library(mve STATIC ${MVE_SOURCES} ${HEADERS})
# target_link_libraries(mve PRIVATE PNG::PNG)

install(TARGETS mve DESTINATION lib)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/math/ 
        DESTINATION include/mve/math 
        FILES_MATCHING PATTERN "*.h")

install(DIRECTORY ${CMAKE_SOURCE_DIR}/acc/ 
        DESTINATION include/mve/acc 
        FILES_MATCHING PATTERN "*.h")

install(DIRECTORY ${CMAKE_SOURCE_DIR}/util/ 
        DESTINATION include/mve/util 
        FILES_MATCHING PATTERN "*.h")

install(DIRECTORY ${CMAKE_SOURCE_DIR}/mve/ 
        DESTINATION include/mve/mve 
        FILES_MATCHING PATTERN "*.h")
