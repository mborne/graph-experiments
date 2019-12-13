# graph-experiments

## Description

Graph processing experimentations with **boost::graph** and **GDAL / OGR** for data access.

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

* Finaliser portage `PathTreeBuilder`

