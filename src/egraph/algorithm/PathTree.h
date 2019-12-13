#pragma once

#include <boost/graph/graph_traits.hpp>
#include <egraph/algorithm/PathTreeNode.h>

#include <map>
#include <algorithm>
#include <limits>

#include <boost/assert.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

namespace egraph {
namespace algorithm {

	/**
	 * @brief builds a shortest path tree
	 */
	template < typename Graph >
	class PathTree {
	public:
        typedef typename boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;
        typedef typename boost::graph_traits<Graph>::edge_descriptor   edge_descriptor;

		typedef PathTreeNode<Graph> node_t;

		/**
		 * A set of nodes indexed according "node.visited"
		 */
		typedef typename boost::multi_index_container<
			node_t,
			boost::multi_index::indexed_by<
				// sort by item::operator<
				boost::multi_index::ordered_unique< boost::multi_index::identity<node_t> >,
				// sort by less<bool> on visited
				boost::multi_index::ordered_non_unique< boost::multi_index::member< node_t, bool, &node_t::visited > >
			>
		> node_set;

		typedef typename node_set::template nth_index<0>::type    marker_vertex_index_t ;
		typedef typename marker_vertex_index_t::iterator          marker_iterator ;
		typedef typename marker_vertex_index_t::const_iterator    const_marker_iterator ;

		typedef typename node_set::template nth_index<1>::type    marker_visited_index_t ;
		typedef typename marker_visited_index_t::iterator         marker_visited_iterator ;
		typedef typename marker_visited_index_t::const_iterator   const_marker_visited_iterator ;


		/**
		 * @brief constructor with a graph
		 */
		PathTree( Graph & graph ):
			_graph(graph)
		{

		}

		/**
		 * @brief mark the vertex as reached with a cost
		 */
		void setRoot( vertex_descriptor root ){
			_markers.clear() ;
			_root = root ;
			_markers.insert( node_t(_root,0.0) ) ;
		}

		/**
		 * @brief get the path to a vertex (empty is not reached)
		 */
		std::vector< edge_descriptor > path( vertex_descriptor target ) const {
			std::vector< edge_descriptor > result ;

			const_marker_iterator it = _markers.find( target );
			if ( it == _markers.end() ){
				return result ;
			}

			while ( it->vertex != _root ){
				result.push_back( it->reachingEdge );
				it = _markers.find( it->reachingEdge.source() ) ;
			}

			std::reverse( result.begin(), result.end() );
			return result ;
		}


		/**
		 * @brief indicates if a vertex is reached
		 */
		inline bool isReached( vertex_descriptor vertex ) const {
			return _markers.find( vertex ) != _markers.end() ;
		}

		/**
		 * @brief get a vertex marker
		 *
		 * @warning the vertex must be reached
		 */
		const node_t & marker( vertex_descriptor vertex ) const {
			marker_iterator it = _markers.template get<0>().find( vertex );
			return *it ;
		}

		/**
		 * @brief add a vertex marker
		 *
		 * @todo check consistency
		 */
		void setMarker( node_t marker ) {
			marker_iterator it = _markers.template get<0>().find( marker.vertex );
			if ( it != _markers.template get<0>().end() ){
				_markers.replace( it, marker );
			}else{
				_markers.insert( marker );
			}
		}

		/**
		 * @brief find the nearest and visited vertex
		 */
		vertex_descriptor findNearestAndNotVisitedVertex() const {
			vertex_descriptor vertex = NULL ;
			double        cost   = std::numeric_limits< double >::infinity() ;

			/*
			 * iterate not visited vertex
			 */
			const marker_visited_index_t & index = visitedIndex() ;
			const_marker_visited_iterator it  = index.lower_bound(false);
			const_marker_visited_iterator end = index.upper_bound(false);
			for ( ; it != end; ++it ){
				const node_t & marker = *it ;
				BOOST_ASSERT( ! marker.visited ) ;

				if ( marker.cost < cost ){
					vertex = marker.vertex ;
					cost   = marker.cost ;
				}
			}

			return vertex ;
		}

		/**
		 * @brief get visited index iterator
		 */
		inline const marker_visited_index_t & visitedIndex() const {
			return _markers.template get<1>() ;
		}
		/**
		 * @brief get visited index iterator
		 */
		inline marker_visited_index_t &       visitedIndex() {
			return _markers.template get<1>() ;
		}


		inline marker_iterator       reached_begin() { return _markers.template get<0>().begin() ; }
		inline const_marker_iterator reached_begin() const { return _markers.template get<0>().begin() ; }
		inline marker_iterator       reached_end() { return _markers.template get<0>().end() ; }
		inline const_marker_iterator reached_end() const { return _markers.template get<0>().end() ; }


	private:
		Graph & _graph ;

		/**
		 * @brief store reached vertices
		 */
		node_set _markers ;
		/**
		 * @brief the root of the tree
		 */
		vertex_descriptor _root ;
	};


} // namespace algorithm
} // namespace graph
