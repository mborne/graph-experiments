#pragma once

#include <iostream>
#include <boost/graph/graph_traits.hpp>

#include <egraph/concept/fid.h>
#include <egraph/concept/cost.h>
#include <egraph/concept/wkt.h>

#include <egraph/routing/PathTree.h>

namespace egraph {
namespace helper {

    /**
     * @brief escape string to CSV using double quotes if needed
     */
    std::string escapeCSV(const std::string & s){
        bool quoted = false;

        std::ostringstream os;
        for ( const char & c : s ){
            if ( c == '"' ){
                os << "\"\"" ;
                quoted = true;
            }else if ( c == ',' ){
                os << c ;
                quoted = true;
            }else{
                os << c ;
            }
        }
        if ( quoted ){
            return std::string("\"")+os.str()+std::string("\"");
        }else{
            return os.str();
        }
    }

    /**
     * @brief write vertices with informations to CSV
     */
    template < typename Graph >
    void verticesToCSV( std::ostream & os, const Graph & graph ){
        using vertex_descriptor = typename boost::graph_traits<Graph>::vertex_descriptor;
        using vertex_iterator   = typename boost::graph_traits<Graph>::vertex_iterator;

        os << "id,in_degree,out_degree,WKT" << std::endl;
        vertex_iterator it,end;
        for ( boost::tie(it,end) = boost::vertices(graph); it != end; ++it ){
            vertex_descriptor vertex = *it;

            // writes infos to CSV
            os << concept::fid(graph[vertex]) ;
            os << "," << boost::in_degree(vertex,graph);
            os << "," << boost::out_degree(vertex,graph);
            os << "," << escapeCSV(concept::wkt(graph[vertex]));
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

        os << "id,source,target,cost,WKT" << std::endl;
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
            os << "," << escapeCSV(concept::wkt(graph[edge]));
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

        os << "id,cost,WKT" << std::endl;
        for ( auto it = pathTree.reached_begin(); it != pathTree.reached_end(); ++it ){
            vertex_descriptor vertex         = it->vertex;
            double cost                      = it->cost;

            // writes infos to CSV
            os << concept::fid( graph[vertex] ) ;
            os << "," << cost ;
            //os << "," << escapeCSV(concept::wkt(graph[vertex]));
            if ( it->isRoot() ){
                os << "," << escapeCSV("GEOMETRYCOLLECTION EMPTY");
            }else{
                os << "," << escapeCSV( concept::wkt( graph[ *(it->reachingEdge) ] ) );
            }
            os << std::endl;
        }
    }


} // namespace csv
} // namespace egraph