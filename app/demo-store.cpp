#include <egraph/Store.h>

using namespace egraph;

int main(int argc, char* argv[]){
    if ( argc != 3 ){
        std::cout << "Usage : demo-gdal <dataset> <layerName>" << std::endl;
        return 0;
    }
    egraph::Store store(argv[1]);
    std::vector<Edge> edges = store.edges(argv[2]);
    // std::cout << edges.size() << std::endl;
    std::cout << "id,source,target,direction,geom" << std::endl;
    for ( const Edge & edge : edges ){
        std::cout << edge.id << "," << edge.source << "," << edge.target << "," << edge.direction << "," << asWKT(edge.geom) << std::endl;
    }
}
