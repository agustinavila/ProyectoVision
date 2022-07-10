cmake_minimum_required(VERSION 3.10)

project(VisionProject VERSION 0.2)
add_compile_definitions(USE_AVX_INSTRUCTIONS=ON)
find_package( OpenCV REQUIRED )
include(FetchContent)
# FetchContent_Declare(OpenCV
# GIT_REPOSITORY https://github.com/opencv/opencv/
#      GIT_TAG        v4.5.3
#      )
#  FetchContent_MakeAvailable(OpenCV)
FetchContent_Declare(dlib
GIT_REPOSITORY https://github.com/davisking/dlib.git
     GIT_TAG        v19.22
     )
FetchContent_MakeAvailable(dlib)
file( COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
include_directories( ${dlib_SOURCE_DIR} )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(include/)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
file(GLOB all_SRCS "${PROJECT_SOURCE_DIR}/include/src/*.cc")
add_executable(mainProyectoVision mainProyectoVision.cc ${all_SRCS})
target_link_libraries( mainProyectoVision dlib)
target_link_libraries( mainProyectoVision ${OpenCV_LIBS} )
add_custom_command(
        TARGET mainProyectoVision POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/config.yaml
                ${CMAKE_CURRENT_BINARY_DIR}/config.yaml)






