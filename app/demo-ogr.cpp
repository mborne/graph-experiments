#include <iostream>

#include <egraph/OGRGraph.h>
#include <gdal/ogrsf_frmts.h>
using namespace egraph;

int main(int argc,char* argv[]){
    OGRGraph graph;
    std::cout << "number of vertices : "<< graph.getNumVertices() << std::endl;
    std::cout << "number of edges : "<< graph.getNumEdges() << std::endl;

    OGRFeatureGraph featureGraph = graph.getFeatureGraph();
    {
        OGRFeatureGraph::vertex_iterator it,end;
        for ( boost::tie(it,end) = boost::vertices(featureGraph); it != end; ++it ){
            OGRFeature* feature = featureGraph[*it];
            std::cout << "v " << feature->GetFID() << std::endl;
        }
    }
    {
        OGRFeatureGraph::edge_iterator it,end;
        for ( boost::tie(it,end) = boost::edges(featureGraph); it != end; ++it ){
            OGRFeature* feature = featureGraph[*it];
            std::cout << "e " << feature->GetFID() ;
            std::cout << " " << feature->GetFieldAsInteger("source") << " -> " << feature->GetFieldAsInteger("target") << std::endl;
        }
    }
    return 0;
}