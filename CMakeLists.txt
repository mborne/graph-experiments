project(DemoBoostGraph)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

add_library(egraph
    src/egraph/OGRGraph.cpp
    src/egraph/helper/ogr.cpp
)
target_link_libraries(egraph
    gdal
    CGAL
)

add_subdirectory(app)

enable_testing()
add_subdirectory(tests)
