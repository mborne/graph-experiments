#include <egraph/Store.h>

using namespace egraph;

int main(int argc, char* argv[]){
    if ( argc != 3 ){
        std::cout << "Usage : demo-gdal <dataset> <layerName>" << std::endl;
        return 0;
    }
    egraph::Store store(argv[1]);
    std::vector<Edge> edges = store.edges(argv[2]);
    std::cout << edges.size() << std::endl;
}
