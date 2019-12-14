#pragma once

#include <boost/optional.hpp>
#include <boost/graph/graph_traits.hpp>

namespace egraph {
namespace routing {

    /**
     * @brief a node in shortest path tree
     */
    template < typename G >
    struct PathTreeNode {
        typedef typename boost::graph_traits<G>::vertex_descriptor vertex_descriptor;
        typedef typename boost::graph_traits<G>::edge_descriptor   edge_descriptor;

        /**
         * @brief constructor
         */
        PathTreeNode(
            vertex_descriptor vertex_ = vertex_descriptor(),
            double cost_ = 0.0
        ):
            vertex(vertex_),
            cost(cost_),
            reachingEdge(),
            visited(false)
        {

        }

        /**
         * @brief indicate if node has reaching edge
         */
        bool isRoot() const {
            return ! reachingEdge.is_initialized() ;
        }

        /**
         * @brief comparator
         */
        inline bool operator < ( const PathTreeNode & other ) const {
            return vertex < other.vertex ;
        }

        /**
         * @brief vertex
         */
        vertex_descriptor vertex ;
        /**
         * @brief cost to reach the vertex
         */
        double            cost ;
        /**
         * @brief directed edge reaching the vertex
         */
        boost::optional<edge_descriptor> reachingEdge ;
        /**
         * @brief indicates if the vertex is visited
         */
        bool          visited ;
    } ;

} // namespace routing
} // namespace egraph
