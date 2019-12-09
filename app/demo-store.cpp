#include <egraph/Store.h>
#include <egraph/Graph.h>

using namespace egraph;

typedef Graph<DefaultVertex,DefaultEdge> graph_t;
typedef graph_t::vertex_handle vertex_handle;
typedef graph_t::edge_handle edge_handle;

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

    graph_t graph;

    std::map<int,vertex_handle> mapVertices;
    for ( const DefaultVertex & vertex : vertices ){
        if ( mapVertices.find(vertex.id) != mapVertices.end() ){
            continue;
        }
        vertex_handle v = graph.addVertex(vertex);
        mapVertices.insert(std::make_pair(vertex.id,v));
    }

    for ( const DefaultEdge & edge : edges ){
        vertex_handle source = mapVertices.find(edge.source)->second;
        vertex_handle target = mapVertices.find(edge.target)->second;
        edge_handle e = graph.addEdge(source,target,edge);
    }

    std::cout << graph.numVertices() << std::endl;
    std::cout << graph.numEdges() << std::endl;
}
