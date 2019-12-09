#ifndef _EGRAPH_ALGORITHM_SHORTESTPATHTREE_H_
#define _EGRAPH_ALGORITHM_SHORTESTPATHTREE_H_

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
	class ShortestPathTree {
	public:
		typedef typename Graph::vertex_handle vertex_handle ;
		typedef typename Graph::directed_edge directed_edge ;


		/**
		 * @brief vertex marker
		 */
		struct marker_t {
			/**
			 * @brief constructor
			 */
			marker_t(
				vertex_handle vertex_ = NULL ,
				double cost_ = 0.0,
				directed_edge reachingEdge_ = directed_edge(),
				bool visited_ = false
			):
				vertex(vertex_),
				cost(cost_),
				reachingEdge(reachingEdge_),
				visited(visited_)
			{

			}

			/**
			 * @brief comparator
			 */
			inline bool operator < ( const marker_t & other ) const {
				return vertex < other.vertex ;
			}

			/**
			 * @brief vertex
			 */
			vertex_handle vertex ;
			/**
			 * @brief cost to reach the vertex
			 */
			double        cost ;
			/**
			 * @brief directed edge reaching the vertex
			 */
			directed_edge reachingEdge ;
			/**
			 * @brief indicates if the vertex is visited
			 */
			bool          visited ;
		} ;

		typedef typename boost::multi_index_container<
			marker_t,
			boost::multi_index::indexed_by<
				// sort by item::operator<
				boost::multi_index::ordered_unique< boost::multi_index::identity<marker_t> >,
				// sort by less<bool> on visited
				boost::multi_index::ordered_non_unique< boost::multi_index::member< marker_t, bool, &marker_t::visited > >
			>
		> marker_set;

		typedef typename marker_set::template nth_index<0>::type  marker_vertex_index_t ;
		typedef typename marker_vertex_index_t::iterator          marker_iterator ;
		typedef typename marker_vertex_index_t::const_iterator    const_marker_iterator ;

		typedef typename marker_set::template nth_index<1>::type  marker_visited_index_t ;
		typedef typename marker_visited_index_t::iterator         marker_visited_iterator ;
		typedef typename marker_visited_index_t::const_iterator   const_marker_visited_iterator ;


		/**
		 * @brief constructor with a graph
		 */
		ShortestPathTree( Graph & graph ):
			_graph(graph)
		{

		}

		/**
		 * @brief mark the vertex as reached with a cost
		 */
		void setRoot( vertex_handle root ){
			_markers.clear() ;
			_root = root ;
			_markers.insert( marker_t(_root,0.0) ) ;
		}

		/**
		 * @brief get the path to a vertex (empty is not reached)
		 */
		std::vector< directed_edge > path( vertex_handle target ) const {
			std::vector< directed_edge > result ;

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
		inline bool isReached( vertex_handle vertex ) const {
			return _markers.find( vertex ) != _markers.end() ;
		}

		/**
		 * @brief get a vertex marker
		 *
		 * @warning the vertex must be reached
		 */
		const marker_t & marker( vertex_handle vertex ) const {
			marker_iterator it = _markers.template get<0>().find( vertex );
			return *it ;
		}

		/**
		 * @brief add a vertex marker
		 *
		 * @todo check consistency
		 */
		void setMarker( marker_t marker ) {
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
		vertex_handle findNearestAndNotVisitedVertex() const {
			vertex_handle vertex = NULL ;
			double        cost   = std::numeric_limits< double >::infinity() ;

			/*
			 * iterate not visited vertex
			 */
			const marker_visited_index_t & index = visitedIndex() ;
			const_marker_visited_iterator it  = index.lower_bound(false);
			const_marker_visited_iterator end = index.upper_bound(false);
			for ( ; it != end; ++it ){
				const marker_t & marker = *it ;
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
		marker_set _markers ;
		/**
		 * @brief the root of the tree
		 */
		vertex_handle _root ;
	};


} // namespace algorithm
} // namespace graph

#endif
