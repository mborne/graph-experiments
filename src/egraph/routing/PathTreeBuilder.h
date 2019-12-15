#pragma once

#include <boost/optional.hpp>
#include <boost/graph/graph_traits.hpp>

#include <egraph/routing/PathTree.h>
#include <egraph/concept/cost.h>
#include <egraph/concept/reverseCost.h>

namespace egraph {
namespace routing {

template < typename G >
class PathTreeBuilder {
public:
    typedef typename boost::graph_traits<G>::vertex_descriptor  vertex_descriptor;
    typedef typename boost::graph_traits<G>::edge_descriptor    edge_descriptor;
    typedef typename boost::graph_traits<G>::out_edge_iterator  out_edge_iterator;
    typedef typename boost::graph_traits<G>::in_edge_iterator   in_edge_iterator;

    typedef typename PathTree<G>::node_type                     node_type;


    PathTreeBuilder(PathTree<G> & pathTree):
        _pathTree(pathTree)
    {

    }

    /**
     * @brief iterate without stop condition
     */
    void build(){
        boost::optional<vertex_descriptor> current;
        while ( (current = findNextVertex()).is_initialized() ){
            visit(*current);
        }
    }

    /**
     * @brief Find next vertex to visit (dijkstra implementation)
     */
    boost::optional<vertex_descriptor> findNextVertex() const {
        boost::optional<vertex_descriptor> result;
        double minCost   = std::numeric_limits< double >::infinity() ;

        auto it  = _pathTree.not_visited_begin();
        auto end = _pathTree.not_visited_end();
        for ( ; it != end; ++it ){
            BOOST_ASSERT( ! it->visited ) ;
            if ( it->cost < minCost ){
                result = it->vertex ;
                minCost = it->cost ;
            }
        }

        return result ;
    }

    /**
     * @brief visit a vertex
     */
    void visit(vertex_descriptor vertex){
        const G & g = _pathTree.graph();

        node_type visitedNode = _pathTree.node(vertex);

        /* visit out edges */
        {
            out_edge_iterator it,end;
            for ( boost::tie(it,end) = boost::out_edges(vertex,g); it != end; ++it ){
                edge_descriptor edge = *it;
                vertex_descriptor reached = boost::target(edge,g);

                double directCost = concept::cost(g[edge]);
                if ( directCost < 0.0 ){
                    continue;
                }
                double newCost = visitedNode.cost + directCost;
                if ( ( ! _pathTree.isReached(reached) ) || newCost < _pathTree.node(reached).cost ){
                    node_type node(reached,newCost);
                    node.reachingEdge = edge;
                    node.visited = false;
                    _pathTree.setNode(node);
                }
            }
        }


        /* visit in edges */
        {
            in_edge_iterator it,end;
            for ( boost::tie(it,end) = boost::in_edges(vertex,g); it != end; ++it ){
                edge_descriptor edge = *it;
                vertex_descriptor reached = boost::source(edge,g);

                double reverseCost = concept::reverseCost(g[edge]);
                if ( reverseCost < 0.0 ){
                    continue;
                }
                double newCost = visitedNode.cost + reverseCost;
                if ( ( ! _pathTree.isReached(reached) ) || newCost < _pathTree.node(reached).cost ){
                    node_type node(reached,newCost);
                    node.reachingEdge = edge;
                    node.visited = false;
                    _pathTree.setNode(node);
                }
            }
        }

        /* mark node as visited */
        visitedNode.visited = true;
        _pathTree.setNode(visitedNode);
    }

private:
    PathTree<G> & _pathTree;
};



} // namespace routing
} // namespace egraph
