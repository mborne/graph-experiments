#include <iostream>

#include <egraph/Graph.h>

using namespace egraph;

/* define graph */
typedef egraph::Graph<
    std::string,       /* vertex properties */
    boost::no_property /* edge properties */
> graph_type;

typedef graph_type::vertex_descriptor vertex_descriptor ;
typedef graph_type::edge_descriptor   edge_descriptor ;
typedef graph_type::vertex_iterator   vertex_iterator ;
typedef graph_type::edge_iterator     edge_iterator ;


int main(int argc, char* argv[]){
    /* create graph */
    graph_type g;

    /* create vertices */
    vertex_descriptor a = boost::add_vertex("A",g);
    vertex_descriptor b = boost::add_vertex("B",g);
    vertex_descriptor c = boost::add_vertex("C",g);

    /* create edges */
    boost::add_edge(a,b,g);
    boost::add_edge(a,c,g);
    boost::add_edge(b,c,g);

    /* list vertices */
    {
        vertex_iterator it, end ;
        for ( boost::tie(it,end) = boost::vertices(g); it != end; ++it ){
            vertex_descriptor v = (*it) ;
            /* retreive vertex properties */
            std::cout << g[v] << std::endl;
        }
    }


    /* list edges */
    {
        edge_iterator it, end ;
        for ( boost::tie(it,end) = boost::edges(g); it != end; ++it ){
            edge_descriptor e = (*it) ;
            vertex_descriptor source = boost::source(e,g);
            vertex_descriptor target = boost::target(e,g);
            /* retreive edge properties */
            std::cout << g[source] << " -> " << g[target] << std::endl;
        }
    }

}

