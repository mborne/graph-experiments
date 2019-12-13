#define BOOST_TEST_MODULE PathTreeTest
#include <boost/test/unit_test.hpp>

#include <egraph/Graph.h>
#include <egraph/algorithm/PathTree.h>
#include <cassert>

using namespace egraph ;
using namespace egraph::algorithm ;

typedef Graph<std::string,double> graph_t;
typedef graph_t::vertex_descriptor vertex_descriptor;
typedef graph_t::edge_descriptor   edge_descriptor;

graph_t createSampleGraph(){
    graph_t g;
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

graph_t::vertex_descriptor findVertex( const std::string & name, const graph_t & g ){
    graph_t::vertex_iterator it,end;
    for ( boost::tie(it,end) = boost::vertices(g); it != end; ++it ){
        if ( g[*it] == name ){
            return *it;
        }
    }
    assert(false);
}

BOOST_AUTO_TEST_SUITE( PathTreeTest )

BOOST_AUTO_TEST_CASE( testSetRoot )
{
    graph_t g = createSampleGraph();
    vertex_descriptor a = findVertex("A",g);
    vertex_descriptor b = findVertex("B",g);
    vertex_descriptor c = findVertex("C",g);

    PathTree<graph_t> pathTree(g);
    pathTree.setRoot(a);

    BOOST_CHECK(pathTree.isReached(a));
    BOOST_CHECK(!pathTree.isReached(b));
    BOOST_CHECK(!pathTree.isReached(c));
}

BOOST_AUTO_TEST_SUITE_END()
