project(DemoBoostGraph)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

add_library(egraph
    src/egraph/FeatureGraphLoader.cpp
    src/egraph/helper/ogr.cpp

    src/egraph/concept/cost.cpp
    src/egraph/concept/reverseCost.cpp
    src/egraph/concept/fid.cpp
    src/egraph/concept/wkt.cpp
)
target_link_libraries(egraph
    gdal
    CGAL
)

add_subdirectory(example)

enable_testing()
add_subdirectory(tests)
