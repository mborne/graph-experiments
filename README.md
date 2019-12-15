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

## Usage

```bash
app/demo-ogr "PG:dbname=gis" "graph.vertex" "graph.edge"
```

## TODO

* Add `concept::id(...): int`
* Add `concept::name(...): string`
* Add `concept::wkt(...): std::string`
* Add `egraph::csv::escape(s): std::string` to manage `"` if needed
* Add `egraph::csv::writeGraph(ostream,graph)` with WKT column
* Add `egraph::csv::writeReachingCost(ostream,pathTree)`

