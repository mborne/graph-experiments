#include "TestGraph.h"

/**
 * @brief find vertex by name
 */
TestGraph::vertex_descriptor findVertex( const std::string & name, const TestGraph & g ){
    TestGraph::vertex_iterator it,end;
    for ( boost::tie(it,end) = boost::vertices(g); it != end; ++it ){
        if ( g[*it] == name ){
            return *it;
        }
    }
    throw std::runtime_error("vertex not found!");
}

TestGraph createSampleGraphA(){
    TestGraph g;
    TestGraph::vertex_descriptor a = boost::add_vertex("A",g);
    TestGraph::vertex_descriptor b = boost::add_vertex("B",g);
    TestGraph::vertex_descriptor c = boost::add_vertex("C",g);
    // A -> B
    boost::add_edge(a,b,1.0,g);
    // A -> C
    boost::add_edge(a,c,2.0,g);
    // B -> C
    boost::add_edge(b,c,0.5,g);
    return g;
}

/**
 * A -> B, A -> C, B -> C
 */
TestGraph createSampleGraphB(){
    using vertex_descriptor = TestGraph::vertex_descriptor;

    TestGraph g;
    vertex_descriptor a = boost::add_vertex("A",g);
    vertex_descriptor b = boost::add_vertex("B",g);
    vertex_descriptor c = boost::add_vertex("C",g);
    // A -> B
    boost::add_edge(a,b,g);
    // A -> C
    boost::add_edge(a,c,g);
    // B -> C
    boost::add_edge(b,c,g);

    return g;
}
