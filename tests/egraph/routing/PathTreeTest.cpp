#include <boost/test/unit_test.hpp>

#include <egraph/Graph.h>
#include <egraph/routing/PathTree.h>
#include <cassert>

#include "../TestGraph.h"

using namespace egraph ;
using namespace egraph::routing ;

BOOST_AUTO_TEST_SUITE( PathTreeTest )

BOOST_AUTO_TEST_CASE( testSetRoot )
{
    TestGraph g = createSampleGraphB();
    TestGraph::vertex_descriptor a = findVertex("A",g);
    TestGraph::vertex_descriptor b = findVertex("B",g);
    TestGraph::vertex_descriptor c = findVertex("C",g);

    PathTree<TestGraph> pathTree(g);
    pathTree.setRoot(a);

    BOOST_CHECK(pathTree.isReached(a));
    BOOST_CHECK(!pathTree.isReached(b));
    BOOST_CHECK(!pathTree.isReached(c));
}

BOOST_AUTO_TEST_SUITE_END()
