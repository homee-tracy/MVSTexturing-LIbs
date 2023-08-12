cmake_minimum_required(VERSION 3.1)

project(Texturing)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'RELWITHDEBINFO' as none was specified.")
    set(CMAKE_BUILD_TYPE RELWITHDEBINFO)
endif()

#Search for TBB library (release build)
set(CMAKE_BUILD_TYPE_BACKUP ${CMAKE_BUILD_TYPE})
set(CMAKE_BUILD_TYPE RELEASE)
# FIND_PACKAGE(TBB REQUIRED)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_BACKUP})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED yes)
add_definitions(-DEIGEN_MPL2_ONLY)

FIND_PACKAGE(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra -Wundef -pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -funroll-loops")
endif()

set(LIB_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
set(EIGEN_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include/eigen3")
set(MVE_INCLUE_DIR "${CMAKE_INSTALL_PREFIX}/include/mve")

message(STATUS "LIB_INCLUDE_DIR: ${LIB_INCLUDE_DIR}")

include_directories(SYSTEM
    ${MVE_INCLUE_DIR}
    ${LIB_INCLUDE_DIR}
    ${EIGEN_INCLUDE_DIR}
)

include_directories(
    libs
)

add_subdirectory(libs)
