# to avoid warnings with <boost/progress.hpp>
add_definitions(-DBOOST_ALLOW_DEPRECATED_HEADERS)

file(GLOB EGRAPH_EXAMPLE_SOURCES *.cpp)

foreach( EGRAPH_EXAMPLE_SOURCE ${EGRAPH_EXAMPLE_SOURCES} )
    get_filename_component(  EGRAPH_EXAMPLE_NAME ${EGRAPH_EXAMPLE_SOURCE} NAME_WE )

    add_executable(${EGRAPH_EXAMPLE_NAME}
        ${EGRAPH_EXAMPLE_SOURCE}
    )
    target_link_libraries(${EGRAPH_EXAMPLE_NAME}
        egraph
        ${Boost_LIBRARIES}
        ${GDAL_LIBRARY}
    )
endforeach()
