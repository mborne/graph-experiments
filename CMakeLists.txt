project(DemoBoostGraph)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

add_library(egraph
    src/egraph/Store.cpp
    src/egraph/LineString.cpp
    src/egraph/Point.cpp
)
target_link_libraries(egraph
    gdal
    CGAL
)

add_executable(demo-boost app/demo-boost.cpp)

add_executable(demo-store app/demo-store.cpp)
target_link_libraries(demo-store
    egraph
)

add_executable(demo-dijkstra app/demo-dijkstra.cpp)
target_link_libraries(demo-dijkstra
    egraph
)

