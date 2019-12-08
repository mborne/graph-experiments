#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <egraph/Vertex.h>
#include <egraph/Edge.h>

namespace egraph {

    using Graph = boost::adjacency_list<
        boost::listS,              /* stable identifiers */
        boost::listS,              /* parallel edges allowed + stable identifiers */
        boost::bidirectionalS,
        Vertex,                    /* vertex properties */
        Edge                       /* edge properties */
    >;

}
