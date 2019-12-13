ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
find_package(Boost COMPONENTS unit_test_framework REQUIRED )
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB EGRAPH_TEST_SOURCES *.cpp)

foreach( EGRAPH_TEST_SOURCE ${EGRAPH_TEST_SOURCES} )
    get_filename_component(  EGRAPH_TEST_NAME ${EGRAPH_TEST_SOURCE} NAME_WE )

    add_executable(${EGRAPH_TEST_NAME}
        ${EGRAPH_TEST_SOURCE}
    )
    target_link_libraries( ${EGRAPH_TEST_NAME}
        egraph
        ${Boost_LIBRARIES}
    )
    add_test(NAME ${EGRAPH_TEST_NAME} COMMAND ${EGRAPH_TEST_NAME})

endforeach()
