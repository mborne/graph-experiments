#include <iostream>
#include <egraph/OGRGraph.h>

#include <gdal/ogrsf_frmts.h>

using namespace egraph;

int main(int argc, char* argv[]){
    if ( argc != 4 ){
        std::cerr << "Usage : demo-ogr <dataset> <vertexLayer> <edgeLayer>" << std::endl;
        std::cerr << "Example : demo-ogr 'PG:dbname=gis' 'graph.vertex' 'graph.edge'" << std::endl;
        return 0;
    }
    std::string path(argv[1]);
    std::string vertexLayerName(argv[2]);
    std::string edgeLayerName(argv[3]);

    OGRGraph graph(argv[1],vertexLayerName,edgeLayerName);
    std::cout << graph.getNumVertices() << " vertices" << std::endl;
    std::cout << graph.getNumEdges() << " edges" << std::endl;

    OGRFeatureGraph featureGraph = graph.getFeatureGraph();
    {
        OGRFeatureGraph::vertex_iterator it,end;
        for ( boost::tie(it,end) = boost::vertices(featureGraph); it != end; ++it ){
            OGRFeature* feature = featureGraph[*it];
            std::cout << "v[" << feature->GetFID() << "]" << std::endl;
        }
    }
    {
        OGRFeatureGraph::edge_iterator it,end;
        for ( boost::tie(it,end) = boost::edges(featureGraph); it != end; ++it ){
            OGRFeature* feature = featureGraph[*it];
            std::cout << "e[" << feature->GetFID() << "] : " ;
            std::cout << feature->GetFieldAsInteger("source") << " -> " << feature->GetFieldAsInteger("target") << std::endl;
        }
    }
}
