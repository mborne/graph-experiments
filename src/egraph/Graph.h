#pragma once

#include <boost/graph/adjacency_list.hpp>

namespace egraph {

    /**
     * @brief alias for boost::adjacency_list for general use graph
     */
    template < typename VertexProperties, typename EdgeProperties >
    using Graph = boost::adjacency_list<
        boost::listS,              /* non stable identifiers */
        boost::listS,              /* parallel edges allowed + stable identifiers */
        boost::bidirectionalS,     /* in and out edges */
        VertexProperties,          /* vertex properties */
        EdgeProperties             /* edge properties */
    >;

}