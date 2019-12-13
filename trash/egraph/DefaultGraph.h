#pragma once

#include <egraph/Graph.h>
#include <egraph/DefaultVertex.h>
#include <egraph/DefaultEdge.h>

namespace egraph {

    using DefaultGraph = Graph<
        DefaultVertex,             /* vertex properties */
        DefaultEdge                /* edge properties */
    >;

}
