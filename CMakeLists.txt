project(DemoBoostGraph)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GDAL "2.3.0" REQUIRED)
find_package(Boost COMPONENTS program_options graph REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${GDAL_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

file(GLOB_RECURSE EGRAPH_SOURCES src/*.cpp)

add_library(egraph
    ${EGRAPH_SOURCES}
)
target_link_libraries(egraph
    ${GDAL_LIBRARY}
    ${Boost_LIBRARIES}
)

add_subdirectory(example)

enable_testing()
add_subdirectory(tests)
