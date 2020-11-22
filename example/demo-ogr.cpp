#include <iostream>
#include <fstream>
#include <chrono>

#include <egraph/FeatureGraphLoader.h>
#include <egraph/routing/PathTreeBuilder.h>

#include <egraph/helper/csv.h>

#define NUM_TREES 20

using namespace egraph;

int main(int argc, char* argv[]){
    /* show help */
    if ( argc != 4 ){
        std::cerr << "Usage : demo-ogr <dataset> <vertexLayer> <edgeLayer>" << std::endl;
        std::cerr << "For example : " << std::endl;
        std::cerr << "example/demo-ogr 'PG:dbname=gis' 'graph.vertex' 'graph.edge'" << std::endl;
        std::cerr << "example/demo-ogr 'PG:dbname=gis' 'graph.vertex' 'graph.edge_distance_weighted'" << std::endl;
        return 0;
    }

    /* retreive parameters */
    std::string path(argv[1]);
    std::string vertexLayerName(argv[2]);
    std::string edgeLayerName(argv[3]);

    /* load a FeatureGraph with GDAL/OGR */
    std::cout << "Load graph vertex_layer=" << vertexLayerName << " edge_layer=" << edgeLayerName << " ..." << std::endl;
    FeatureGraphLoader loader(path);
    FeatureGraph graph = loader.getFeatureGraph(vertexLayerName,edgeLayerName);

    /* display the number of vertices */
    std::cout << "Number of vertices : " << boost::num_vertices(graph) << std::endl;
    std::cout << "Number of edges : " << boost::num_edges(graph) << std::endl;

    /* display vertices with in/out degree */
    std::cout << "Dump vertices with informations to vertices.csv ..." << std::endl;
    {
        std::ofstream ofs("vertices.csv");
        helper::verticesToCSV(ofs,graph);
    }

    /* display edges */
    std::cout << "Dump edges with informations to edges.csv ..." << std::endl;
    {
        std::ofstream ofs("edges.csv");
        helper::edgesToCSV(ofs,graph);
    }

    /* build path trees for some vertex */
    {
        int count = 0;
        FeatureGraph::vertex_iterator it,end;
        for ( boost::tie(it,end) = boost::vertices(graph); it != end && count < NUM_TREES; ++it, ++count ){
            FeatureGraph::vertex_descriptor origin = *it;
            int originId = concept::fid( graph[origin] );
            std::cout << "build path tree from " << originId << "..." << std::endl;

            auto start = std::chrono::system_clock::now();
            routing::PathTree<FeatureGraph> pathTree(graph);
            pathTree.setRoot(origin);
            routing::PathTreeBuilder<FeatureGraph> pathTreeBuilder(pathTree);
            pathTreeBuilder.build();
            auto end  = std::chrono::system_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end-start);
            std::cout << "elapsed " << originId << " : " << elapsed.count() << " s" << std::endl;

            std::string ofsName("distance-from-");
            ofsName += std::to_string(originId);
            ofsName += ".csv";
            std::cout << "save result to " << ofsName << std::endl;
            std::ofstream ofs(ofsName.c_str());
            helper::pathTreeToCSV(ofs,pathTree);
        }
    }

}
