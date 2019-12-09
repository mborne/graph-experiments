#include <egraph/Store.h>
#include <egraph/DefaultGraph.h>
#include <egraph/GraphBuilder.h>

using namespace egraph;

int main(int argc, char* argv[]){
    if ( argc != 4 ){
        std::cout << "Usage : demo-gdal <dataset> <edgeLayer> <vertexLayer>" << std::endl;
        return 0;
    }
    egraph::Store store(argv[1]);
    std::vector<DefaultEdge> edges = store.edges(argv[2]);
    std::vector<DefaultVertex> vertices = store.vertices(argv[3]);
    std::cout << vertices.size() << " vertices" << std::endl;
    std::cout << edges.size() << " edges" << std::endl;

    DefaultGraph graph;
    {
        GraphBuilder builder(graph);
        for ( const DefaultVertex & vertex : vertices ){
            builder.addVertex(vertex);
        }
        for ( const DefaultEdge & edge : edges ){
            builder.addEdge(edge);
        }
    }

    {
        DefaultGraph::vertex_iterator it,end;
        for ( boost::tie(it,end) = boost::vertices(graph); it != end; ++it ){
            DefaultGraph::vertex_descriptor v = *it;
            std::cout << graph[v].id << " in : " << boost::in_degree(v,graph) << std::endl;
        }
    }


}
