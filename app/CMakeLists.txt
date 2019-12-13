add_executable(demo-boost demo-boost.cpp)
target_link_libraries(demo-boost
    egraph
)

add_executable(demo-ogr demo-ogr.cpp)
target_link_libraries(demo-ogr
    egraph
)

# add_executable(demo-dijkstra demo-dijkstra.cpp)
# target_link_libraries(demo-dijkstra
#     egraph
# )
