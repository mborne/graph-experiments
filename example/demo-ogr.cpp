#include <iostream>
#include <fstream>

#include <egraph/FeatureGraphLoader.h>
#include <egraph/concept/cost.h>

#include <egraph/routing/PathTreeBuilder.h>

#include <gdal/ogrsf_frmts.h>

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
    FeatureGraphLoader loader(path,vertexLayerName,edgeLayerName);
    FeatureGraph graph = loader.getFeatureGraph();

    /* display the number of vertices */
    std::cout << "Number of vertices : " << boost::num_vertices(graph) << std::endl;
    std::cout << "Number of edges : " << boost::num_edges(graph) << std::endl;

    /* display vertices with in/out degree */
    std::cout << "Dump vertices with informations to vertices.csv ..." << std::endl;
    {
        std::ofstream ofs("vertices.csv");
        ofs << "id,in_degree,out_degree" << std::endl;
        FeatureGraph::vertex_iterator it,end;
        for ( boost::tie(it,end) = boost::vertices(graph); it != end; ++it ){
            FeatureGraph::vertex_descriptor vertex = *it;
            FeaturePtr feature = graph[vertex];

            // writes infos to CSV
            ofs << feature->GetFID() ;
            ofs << "," << boost::in_degree(vertex,graph);
            ofs << "," << boost::out_degree(vertex,graph);
            ofs << std::endl;
        }
    }

    /* display edges */
    std::cout << "Dump edges with informations to edges.csv ..." << std::endl;
    {
        std::ofstream ofs("edges.csv");
        ofs << "id,source,target,cost" << std::endl;
        FeatureGraph::edge_iterator it,end;
        for ( boost::tie(it,end) = boost::edges(graph); it != end; ++it ){
            FeatureGraph::edge_descriptor edge = *it;
            FeaturePtr feature = graph[edge];

            // writes infos to CSV
            ofs << feature->GetFID();
            ofs << "," << feature->GetFieldAsInteger("source") ;
            ofs << "," << feature->GetFieldAsInteger("target") ;
            ofs << "," << concept::cost(feature) ;
            ofs << std::endl;
        }
    }

    /* build path trees for some vertex */
    {
        FeatureGraph::vertex_iterator it,end;
        for ( boost::tie(it,end) = boost::vertices(graph); it != end; ++it ){
            FeatureGraph::vertex_descriptor origin = *it;
            FeaturePtr feature = graph[origin];

            std::cout << "build path tree from " << feature->GetFID() << "..." << std::endl;
            routing::PathTree<FeatureGraph> pathTree(graph);
            pathTree.setRoot(origin);
            routing::PathTreeBuilder<FeatureGraph> pathTreeBuilder(pathTree);
            pathTreeBuilder.build();
        }
    }

}
