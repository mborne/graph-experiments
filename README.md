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

* Renommer algorithm en model
* `DijsktraVisitor`

```cxx
class DijsktraVisitor {
    // false si aucun sommet trouvé
    bool visit(const PathTree<G>& pathTree){
        // recherche du sommet à visiter (plus proche de la racine)

        // exploration des arcs sortants

        // exploration des arcs entrants

    }
}
```

* Calcul de plus court chemin

```cxx
std::vector<edge_descriptor> findPath(graph, origin, destination, visitor){
    PathTree pathTree(graph);
    pathTree.setRoot(origin);
    while ( visitor.visit(pathTree) ){
        if ( pathTree.isReached(destination) ){
            return pathTree.buildPath(destination);
        }
    }
    // Not found
}
```

