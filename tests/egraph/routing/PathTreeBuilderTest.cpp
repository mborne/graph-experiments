#include <boost/test/unit_test.hpp>

#include <egraph/Graph.h>
#include <egraph/routing/PathTree.h>
#include <egraph/routing/PathTreeBuilder.h>
#include <cassert>

#include "../TestGraph.h"

using namespace egraph ;
using namespace egraph::routing ;

BOOST_AUTO_TEST_SUITE( PathTreeBuilderTest )

BOOST_AUTO_TEST_CASE( testFindNextVertex )
{
    using vertex_descriptor = TestGraph::vertex_descriptor;

    TestGraph g = createSampleGraphA();
    vertex_descriptor a = findVertex("A",g);
    vertex_descriptor b = findVertex("B",g);
    vertex_descriptor c = findVertex("C",g);

    PathTree<TestGraph> pathTree(g);
    PathTreeBuilder<TestGraph> builder(pathTree);
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
    using vertex_descriptor = TestGraph::vertex_descriptor;
    using edge_descriptor = TestGraph::edge_descriptor;

    TestGraph g = createSampleGraphA();
    vertex_descriptor a = findVertex("A",g);
    vertex_descriptor b = findVertex("B",g);
    vertex_descriptor c = findVertex("C",g);

    PathTree<TestGraph> pathTree(g);
    pathTree.setRoot(a);
    PathTreeBuilder<TestGraph> builder(pathTree);
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
