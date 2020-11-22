ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
find_package(Boost COMPONENTS unit_test_framework REQUIRED )
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE EGRAPH_TEST_SOURCES *.cpp)
add_executable(egraph-test ${EGRAPH_TEST_SOURCES} )
target_link_libraries( egraph-test
    egraph
    ${Boost_LIBRARIES}
)
add_test(NAME egraph-test COMMAND egraph-test)
