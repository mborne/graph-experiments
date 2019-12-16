# graph-experiments

## Description

Graph processing experiments based on **boost::graph** and **GDAL / OGR** to load data.

## Build

```bash
mkdir -p Debug
cd Debug
cmake ..
make
make test
```

## Examples

* [example/demo-boost.cpp](example/demo-boost.cpp) : How to use `boost::graph`
* [example/demo-dijkstra.cpp](example/demo-dijkstra.cpp) : Shortest path computation

```bash
example/demo-ogr "PG:dbname=gis" "graph.vertex" "graph.edge"
# or
example/demo-ogr "PG:dbname=gis" "graph.vertex" "graph.edge_distance_weighted"
```

## TODO

* [ ] Optimize `PathTreeBuilder::findNextVertex`
* [ ] Add `concept::wkt(...): std::string`
* [ ] Add `egraph::csv::escape(s): std::string` to manage `"` if needed

## Performance debug

```bash
valgrind --tool=callgrind example/demo-ogr 'PG:dbname=gis' 'graph.vertex' 'graph.edge_distance_weighted'
kcachegrind $(ls -tr callgrind.out.* | tail -1)
```
