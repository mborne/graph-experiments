project(DemoBoostGraph)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ensure a .lib is created
if (CMAKE_BUILD_SHARED)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

find_package(GDAL "2.3.0" REQUIRED)
message("-- Found GDAL ${GDAL_VERSION}")

set (Boost_USE_STATIC_LIBS OFF CACHE BOOL "use static libraries from Boost")
find_package(Boost COMPONENTS program_options graph REQUIRED)
message("-- Found Boost ${Boost_VERSION}")

include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

if (WIN32)
  # disable autolinking in boost
  add_definitions( -DBOOST_ALL_NO_LIB )

  # force all boost libraries to dynamic link (we already disabled
  # autolinking, so I don't know why we need this, but we do!)
  add_definitions( -DBOOST_ALL_DYN_LINK )
endif()

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
