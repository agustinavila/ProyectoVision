cmake_minimum_required(VERSION 3.14)
project(UnitTests)
set(CMAKE_CXX_STANDARD 17)

# Include OpenCV
find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Include googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

include_directories(../include/)

file(GLOB analizadorlandmarks_ "../src/analizadorlandmarks.cc")
add_library(analizadorlandmarks ${analizadorlandmarks_})

add_executable( analizadorlandmarks_test  analizadorlandmarks_test.cc )

target_link_libraries( analizadorlandmarks_test GTest::gtest_main )
target_link_libraries( analizadorlandmarks_test ${OpenCV_LIBS} )
target_link_libraries( analizadorlandmarks_test analizadorlandmarks )
include(GoogleTest)
gtest_discover_tests(analizadorlandmarks_test)