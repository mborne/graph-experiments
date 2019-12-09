#pragma once

#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <egraph/DefaultVertex.h>
#include <egraph/DefaultEdge.h>

namespace egraph {

    using DefaultGraph = boost::adjacency_list<
        boost::listS,              /* stable identifiers */
        boost::listS,              /* parallel edges allowed + stable identifiers */
        boost::bidirectionalS,
        DefaultVertex,             /* vertex properties */
        DefaultEdge                /* edge properties */
    >;

    typedef boost::graph_traits<DefaultGraph>::vertex_descriptor vertex_descriptor;
    typedef boost::graph_traits<DefaultGraph>::edge_descriptor   edge_descriptor;

}
