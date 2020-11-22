# graph-experiments

## Description

Graph processing experiments based on **boost::graph** and **GDAL / OGR** to load data.

## Build

```bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
make test
```

## Examples

* [example/demo-boost.cpp](example/demo-boost.cpp) : Some notes to use `boost::graph`
* [example/demo-dijkstra.cpp](example/demo-dijkstra.cpp) : Shortest path computation
* [example/demo-ogr.cpp](example/demo-ogr.cpp) : Load `FeatureGraph` using GDAL/OGR and compute some `ShortestPathTree`

```bash
example/demo-ogr "PG:dbname=gis" "graph.vertex" "graph.edge"
# or
example/demo-ogr "PG:dbname=gis" "graph.vertex" "graph.edge_distance_weighted"
```

![Dijkstra shortest path tree](img/path-tree-1.png)

## Performance debug

```bash
valgrind --tool=callgrind example/demo-ogr 'PG:dbname=gis' 'graph.vertex' 'graph.edge_distance_weighted'
kcachegrind $(ls -tr callgrind.out.* | tail -1)
```
