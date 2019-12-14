#define BOOST_TEST_MODULE PathTreeBuilderTest
#include <boost/test/unit_test.hpp>

#include <egraph/Graph.h>
#include <egraph/routing/PathTree.h>
#include <egraph/routing/PathTreeBuilder.h>
#include <cassert>

using namespace egraph ;
using namespace egraph::routing ;

typedef Graph<std::string,double> graph_t;
typedef graph_t::vertex_descriptor vertex_descriptor;
typedef graph_t::edge_descriptor   edge_descriptor;

graph_t createSampleGraph(){
    graph_t g;
    vertex_descriptor a = boost::add_vertex("A",g);
    vertex_descriptor b = boost::add_vertex("B",g);
    vertex_descriptor c = boost::add_vertex("C",g);
    // A -> B
    boost::add_edge(a,b,1.0,g);
    // A -> C
    boost::add_edge(a,c,2.0,g);
    // B -> C
    boost::add_edge(b,c,0.5,g);
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

BOOST_AUTO_TEST_SUITE( PathTreeBuilderTest )

BOOST_AUTO_TEST_CASE( testFindNextVertex )
{
    graph_t g = createSampleGraph();
    vertex_descriptor a = findVertex("A",g);
    vertex_descriptor b = findVertex("B",g);
    vertex_descriptor c = findVertex("C",g);

    PathTree<graph_t> pathTree(g);
    PathTreeBuilder<graph_t> builder(pathTree);
    // pas de sommet à visité si pas de racine
    {
        boost::optional<vertex_descriptor> result = builder.findNextVertex();
        BOOST_REQUIRE(!result.is_initialized());
    }
    pathTree.setRoot(a);
    // racine une fois initialisée
    {
        boost::optional<vertex_descriptor> result = builder.findNextVertex();
        BOOST_REQUIRE(result.is_initialized());
        BOOST_CHECK_EQUAL(*result,a);
    }
}



BOOST_AUTO_TEST_CASE( testBuildFull )
{
    graph_t g = createSampleGraph();
    vertex_descriptor a = findVertex("A",g);
    vertex_descriptor b = findVertex("B",g);
    vertex_descriptor c = findVertex("C",g);

    PathTree<graph_t> pathTree(g);
    pathTree.setRoot(a);
    PathTreeBuilder<graph_t> builder(pathTree);
    builder.build();

    BOOST_CHECK(pathTree.isReached(a));
    BOOST_CHECK_EQUAL(pathTree.node(a).cost,0.0);
    BOOST_CHECK(!pathTree.node(a).reachingEdge.is_initialized() );

    BOOST_CHECK(pathTree.isReached(b));
    BOOST_CHECK_EQUAL(pathTree.node(b).cost,1.0);
    BOOST_CHECK(pathTree.node(b).reachingEdge.is_initialized() );

    BOOST_CHECK(pathTree.isReached(c));
    BOOST_CHECK_EQUAL(pathTree.node(c).cost,1.5);
    BOOST_CHECK(pathTree.node(c).reachingEdge.is_initialized() );

    std::vector< edge_descriptor > path = pathTree.path(c);
    BOOST_CHECK_EQUAL(path.size(),2);
}

BOOST_AUTO_TEST_SUITE_END()
