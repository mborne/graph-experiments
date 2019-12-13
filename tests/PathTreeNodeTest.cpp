#define BOOST_TEST_MODULE PathTreeNodeTest
#include <boost/test/unit_test.hpp>

#include <egraph/Graph.h>
#include <egraph/algorithm/PathTreeNode.h>

using namespace egraph ;
using namespace egraph::algorithm ;

typedef Graph<int,double> graph_t;

BOOST_AUTO_TEST_SUITE( PathTreeNodeTest )

BOOST_AUTO_TEST_CASE( testDefaultConstructor )
{
    PathTreeNode<graph_t> node;
    BOOST_CHECK( ! node.visited ) ;
    BOOST_CHECK( ! node.reachingEdge ) ;
    BOOST_CHECK_EQUAL(node.cost,0.0) ;
}

BOOST_AUTO_TEST_SUITE_END()
