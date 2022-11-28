# MAIN PROJECT PROPERTIES
# <==============================================================>
cmake_minimum_required(VERSION 3.1)
message("\n########################################################")
message("################## CMAKE IS STARTING ###################")
message("########################################################\n")


if(WIN32)
    message("WINDOWS OS DETECTED\n")
    SET(COMPILER_PATH C:/mingw64/bin)
    SET(CMAKE_C_COMPILER ${COMPILER_PATH}/gcc.exe CACHE STRING "gcc compiler" FORCE)
    SET(CMAKE_CXX_COMPILER ${COMPILER_PATH}/g++.exe CACHE STRING "g++ compiler" FORCE)
    SET(CMAKE_MAKE_PROGRAM ${COMPILER_PATH}/mingw32-make.exe CACHE STRING "make command" FORCE)
    SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/share/cmake-3.25/Modules)
    SET(OpenCV_DIR "C:/Users/xresayar/Programs/OpenCV/4.5.5/build")
endif(WIN32)
project(ImageProcessing)


# SET PROJECT FILES
# <==============================================================>
set(SOURCES 
    main.cpp)
add_executable(ImageProcessing ${SOURCES})


# OPENCV PROPERTIES
# <==============================================================>
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(ImageProcessing ${OpenCV_LIBS})


# TEST : VARIABLES
# <==============================================================>
message("\n########################################################")
message("###################### VARIABLES #######################")
message("########################################################")
message(STATUS "OpenCV library status:")
message(STATUS "    ---> CONFIG: ${OpenCV_DIR}")
message(STATUS "    ---> VERSION: ${OpenCV_VERSION}")
message(STATUS "    ---> LIBRARIES: ${OpenCV_LIBS}")
message(STATUS "    ---> INCLUDE PATH: ${OpenCV_INCLUDE_DIRS}")
message("########################################################")
message("########################################################")
message("########################################################\n")

#SET(OpenCV_LIBS "C:/Users/xresayar/Programs/OpenCV/4.5.5/build/x64/mingw/lib")
#SET(OpenCV_INCLUDE_DIRS "C:/Users/xresayar/Programs/OpenCV/4.6.0/build/include")
#find_package(OpenCV REQUIRED PATHS C:/Users/xresayar/Programs/OpenCV/build)