cmake_minimum_required(VERSION 3.18)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if(WIN32)
    SET(COMPILER_PATH C:/MinGW/bin)
    SET(CMAKE_C_COMPILER ${COMPILER_PATH}/gcc.exe)
    SET(CMAKE_CXX_COMPILER ${COMPILER_PATH}/g++.exe)
endif(WIN32)
project(ImageProcessing)


find_package(OpenCV REQUIRED)

set(SOURCES main.cpp)
add_executable(ImageProcessing ${SOURCES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(ImageProcessing ${OpenCV_LIBS})



#set(CMAKE_PREFIX_PATH C:/Users/xresayar/Programs/OpenCV/build)
#find_package(OpenCV REQUIRED PATHS C:/Users/xresayar/Programs/OpenCV/build)
#include_directories(${OpenCV_INCLUDE_DIRS})
#target_include_directories(ImageProcessing PUBLIC C:/Users/xresayar/Programs/OpenCV/build/include)
#target_link_libraries(ImageProcessing PUBLIC C:/Users/xresayar/Programs/OpenCV/build/x64/vc15/lib/opencv_world460.lib)
#TARGET_LINK_LIBRARIES(ImageProcessing ${OpenCV_LIBS})
#SET(OpenCV_DIR C:/Users/xresayar/Programs/OpenCV/build/)
#FIND_PACKAGE(OpenCV REQUIRED PATHS OpenCV_DIR)
#include_directories(${OpenCV_INCLUDE_DIRS})
#link_directories(${OpenCV_LIB_DIR})
#target_link_libraries(ImageProcessing ${OpenCV_LIBS})
#install(TARGETS ImageProcessing DESTINATION build)
#target_link_libraries( DisplayImage ${OpenCV_LIBS} )
