cmake_minimum_required(VERSION 3.10)

# Project name
project(VisionProject VERSION 0.2)

# check for debug/release
set(CMAKE_DEBUG_POSTFIX d)
add_library(tutorial_compiler_flags INTERFACE)

# Include OpenCV
find_package( OpenCV 4.0.0 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Include Dlib v19.22
include(FetchContent)
FetchContent_Declare(dlib
GIT_REPOSITORY https://github.com/davisking/dlib.git
GIT_TAG        v19.22
)
FetchContent_MakeAvailable(dlib)
include_directories( ${dlib_SOURCE_DIR} )

# Copy 'data' folder to destination folder
file( COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(include/)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Wpedantic -Wno-ignored-qualifiers)
add_compile_definitions(USE_AVX_INSTRUCTIONS=ON)

add_executable(mainProyectoVision mainProyectoVision.cc)

add_subdirectory(src)
# add_subdirectory(test)
target_link_libraries( mainProyectoVision dlib)
target_link_libraries( mainProyectoVision fuente)
target_link_libraries( mainProyectoVision ${OpenCV_LIBS} )

# Copy necessary files to build folder
add_custom_command(
        TARGET mainProyectoVision POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/config.yaml
                ${CMAKE_CURRENT_BINARY_DIR}/config.yaml)






