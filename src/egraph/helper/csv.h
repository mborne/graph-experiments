#pragma once

#include <iostream>
#include <boost/graph/graph_traits.hpp>

#include <egraph/concept/fid.h>
#include <egraph/concept/cost.h>

#include <egraph/routing/PathTree.h>

namespace egraph {
namespace helper {

    /**
     * @brief write vertices with informations to CSV
     */
    template < typename Graph >
    void verticesToCSV( std::ostream & os, const Graph & graph ){
        using vertex_descriptor = typename boost::graph_traits<Graph>::vertex_descriptor;
        using vertex_iterator   = typename boost::graph_traits<Graph>::vertex_iterator;

        os << "id,in_degree,out_degree" << std::endl;
        vertex_iterator it,end;
        for ( boost::tie(it,end) = boost::vertices(graph); it != end; ++it ){
            vertex_descriptor vertex = *it;

            // writes infos to CSV
            os << concept::fid(graph[vertex]) ;
            os << "," << boost::in_degree(vertex,graph);
            os << "," << boost::out_degree(vertex,graph);
            os << std::endl;
        }
    }

    /**
     * @brief write edges with informations to CSV
     */
    template < typename Graph >
    void edgesToCSV( std::ostream & os, const Graph & graph ){
        using vertex_descriptor = typename boost::graph_traits<Graph>::vertex_descriptor;
        using edge_descriptor   = typename boost::graph_traits<Graph>::edge_descriptor;
        using edge_iterator     = typename boost::graph_traits<Graph>::edge_iterator;

        os << "id,source,target,cost" << std::endl;
        edge_iterator it,end;
        for ( boost::tie(it,end) = boost::edges(graph); it != end; ++it ){
            edge_descriptor edge = *it;

            vertex_descriptor source = boost::source(edge,graph);
            vertex_descriptor target = boost::target(edge,graph);

            // writes infos to CSV
            os << concept::fid( graph[edge] ) ;
            os << "," << concept::fid( graph[source] ) ;
            os << "," << concept::fid( graph[target] ) ;
            os << "," << concept::cost( graph[edge] ) ;
            os << std::endl;
        }
    }

    /**
     * @brief writes distance to reached vertices to CSV
     */
    template < typename Graph >
    void pathTreeToCSV( std::ostream & os, const routing::PathTree<Graph> & pathTree ){
        using vertex_descriptor = typename boost::graph_traits<Graph>::vertex_descriptor;
        using edge_descriptor   = typename boost::graph_traits<Graph>::edge_descriptor;
        using edge_iterator     = typename boost::graph_traits<Graph>::edge_iterator;

        const Graph & graph = pathTree.graph();

        os << "id,cost" << std::endl;
        for ( auto it = pathTree.reached_begin(); it != pathTree.reached_end(); ++it ){
            vertex_descriptor vertex = it->vertex;
            double cost              = it->cost;

            // writes infos to CSV
            os << concept::fid( graph[vertex] ) ;
            os << "," << cost ;
            os << std::endl;
        }
    }


} // namespace csv
} // namespace egraph