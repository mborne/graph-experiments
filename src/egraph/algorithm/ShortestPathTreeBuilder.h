#ifndef _EGRAPH_ALGORITHM_SHORTESTPATHTREEBUILDER_H_
#define _EGRAPH_ALGORITHM_SHORTESTPATHTREEBUILDER_H_

#include <limits>

#include <egraph/concept/cost.h>

#include <egraph/algorithm/ShortestPathTree.h>

namespace egraph {
namespace algorithm {

	/**
	 * @brief builds a shortest path tree
	 */
	template < typename Graph >
	class ShortestPathTreeBuilder {
	public:
		typedef typename Graph::vertex_handle vertex_handle ;
		typedef typename Graph::directed_edge directed_edge ;

		typedef ShortestPathTree< Graph >      tree_t ;
		typedef typename tree_t::marker_t      marker_t ;

		/**
		 * @brief constructor with a graph
		 */
		ShortestPathTreeBuilder( Graph & graph ):
			_tree(graph),
			_maxCost( std::numeric_limits< double >::infinity() ),
			_targetVertex( NULL )
		{

		}

		/**
		 * @brief build the shortest path tree from a root vertex
		 */
		void buildTree( vertex_handle root ){
			_tree.setRoot( root );

			// find the next vertex to visit
			vertex_handle current = NULL ;
			while ( ( current = findNextVertex() ) != NULL ) {
				// break if maxCost is reached
				if ( _tree.marker( current ).cost > _maxCost ){
					break;
				}
				// break is target vertex is reached
				if ( _targetVertex != NULL && _tree.isReached(_targetVertex) ){
					break;
				}
				visitVertex( current );
			}
		}

		/**
		 * @brief visit a vertex
		 */
		void visitVertex( vertex_handle visitedVertex ){
			// reach each posible vertex from visitedVertex
			std::vector< directed_edge > edges = visitedVertex->incidentEdges() ;

			marker_t visitedMarker = _tree.marker( visitedVertex ) ;

			for ( size_t i = 0; i < edges.size(); i++ ){
				const directed_edge & edge = edges[i] ;

				vertex_handle reachedVertex = edge.target() ;
				double newCost = visitedMarker.cost + concept::cost( edge.handle->properties() );
				if ( ! _tree.isReached( reachedVertex ) ){
					//first reach
					_tree.setMarker( marker_t( reachedVertex, newCost, edge ) );
				}else{
					//is better?
					marker_t reachedMarker = _tree.marker( reachedVertex );
					if ( newCost < reachedMarker.cost ){
						reachedMarker.cost = newCost ;
						reachedMarker.reachingEdge = edge ;
						_tree.setMarker( reachedMarker );
					}
				}
			}
			//mark as visited
			visitedMarker.visited = true ;
			_tree.setMarker( visitedMarker );
		}


		/**
		 * @brief find the next vertex to visit
		 *
		 * @return the vertex handle, NULL if not found
		 */
		vertex_handle findNextVertex() const {
			return _tree.findNearestAndNotVisitedVertex() ;
		}

		/**
		 * @brief get the shortest path tree
		 */
		inline const ShortestPathTree< Graph > & tree() const {
			return _tree ;
		}
		/**
		 * @brief get the shortest path tree
		 */
		inline ShortestPathTree< Graph > & tree() {
			return _tree ;
		}


		double maxCost() const {
			return _maxCost ;
		}
		void setMaxCost( double maxCost ){
			_maxCost = maxCost ;
		}

		vertex_handle targetVertex() {
			return _targetVertex ;
		}
		void setTargetVertex( vertex_handle targetVertex ){
			_targetVertex = targetVertex ;
		}

	private:
		ShortestPathTree< Graph > _tree ;
		double _maxCost ;
		vertex_handle _targetVertex ;
	};


} // namespace algorithm
} // namespace graph

#endif
