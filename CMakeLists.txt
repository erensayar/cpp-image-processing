# MAIN PROJECT PROPERTIES
# <==============================================================>
cmake_minimum_required(VERSION 3.18)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if(WIN32)
    # Set Compiler DIR
    SET(COMPILER_PATH C:/MinGW/bin)
    SET(CMAKE_C_COMPILER ${COMPILER_PATH}/gcc.exe)
    SET(CMAKE_CXX_COMPILER ${COMPILER_PATH}/g++.exe)
endif(WIN32)
project(ImageProcessing)


# SET PROJECT FILES
# <==============================================================>
set(SOURCES main.cpp)
add_executable(ImageProcessing ${SOURCES})


# OPENCV PROPERTIES
# <==============================================================>
SET(OpenCV_DIR "C:/Users/xresayar/Programs/OpenCV/4.5.5/build")
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(ImageProcessing ${OpenCV_LIBS})


# TEST : VARIABLES
# <==============================================================>
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


#SET(OpenCV_LIBS "C:/Users/xresayar/Programs/OpenCV/4.5.5/build/x64/mingw/lib")
#SET(OpenCV_INCLUDE_DIRS "C:/Users/xresayar/Programs/OpenCV/4.6.0/build/include")
#find_package(OpenCV REQUIRED PATHS C:/Users/xresayar/Programs/OpenCV/build)