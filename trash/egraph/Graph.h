#ifndef _EGRAPH_GRAPH_H_
#define _EGRAPH_GRAPH_H_

#include <set>

#include <egraph/Direction.h>
#include <egraph/Vertex.h>
#include <egraph/Edge.h>

namespace egraph {

	/**
	 * @brief graph
	 */
	template < typename VertexProperties, typename EdgeProperties >
	class Graph {
	public:
		typedef Graph< VertexProperties, EdgeProperties > self ;

		typedef VertexProperties             vertex_properties ;
		typedef EdgeProperties               edge_properties ;

		typedef Vertex< self >               vertex_t ;
		typedef Edge< self >                 edge_t ;

		typedef vertex_t *                   vertex_handle ;
		typedef edge_t *                     edge_handle ;

		typedef std::set< vertex_t* >        vertex_set ;
		typedef std::set< edge_t* >          edge_set ;

		typedef typename vertex_set::iterator       vertex_iterator ;
		typedef typename vertex_set::const_iterator const_vertex_iterator ;

		typedef typename edge_set::iterator         edge_iterator ;
		typedef typename edge_set::const_iterator   const_edge_iterator ;

		/**
		 * @brief an edge with a direction
		 */
		struct directed_edge {
			/**
			 * @brief constructor with an edge and a direction
			 */
			directed_edge(
				edge_handle edge = NULL,
				Direction direction = DIRECT
			):
				handle(edge),
				direction(direction)
			{

			}

			/**
			 * @brief get the source for the directed edge taking direction in account
			 */
			vertex_handle source() const {
				return direction == DIRECT ? handle->source() : handle->target() ;
			}
			/**
			 * @brief get the source for the directed edge taking direction in account
			 */
			vertex_handle target() const {
				return direction == DIRECT ? handle->target() : handle->source() ;
			}

			edge_handle handle ;
			Direction   direction ;
		};

		/**
		 * @brief default constructor
		 */
		Graph():
			_vertices(),
			_edges()
		{

		}
		/**
		 * @brief destructor
		 */
		virtual ~Graph()
		{
			for ( edge_iterator it = edges_begin(); it != edges_end(); ++it ){
				delete *it ;
			}
			for ( vertex_iterator it = vertices_begin(); it != vertices_end(); ++it ){
				delete *it ;
			}
		}

		/**
		 * @brief create a new vertex
		 */
		vertex_handle addVertex( const vertex_properties & properties = vertex_properties() ){
			vertex_handle v = new vertex_t( properties ) ;
			_vertices.insert( v ) ;
			return v ;
		}

		/**
		 * @brief create a new edge
		 */
		edge_handle addEdge(
			vertex_handle source,
			vertex_handle target,
			const edge_properties & properties = edge_properties()
		){
			assert( isValid(source) );
			assert( isValid(target) );

			edge_handle e = new edge_t( source, target, properties ) ;
			_edges.insert( e ) ;
			return e ;
		}

		int numVertices() const {
			return _vertices.size();
		}

		int numEdges() const {
			return _edges.size();
		}

		/**
		 * indicates if the vertex is valid
		 */
		bool isValid( vertex_handle vertex ) const {
			return _vertices.find( vertex ) != _vertices.end() ;
		}
		/**
		 * indicates if the vertex is valid
		 */
		bool isValid( edge_handle edge ) const {
			return _edges.find( edge ) != _edges.end() ;
		}

		inline vertex_iterator       vertices_begin() { return _vertices.begin() ; }
		inline const_vertex_iterator vertices_begin() const { return _vertices.begin() ; }
		inline vertex_iterator       vertices_end() { return _vertices.end() ; }
		inline const_vertex_iterator vertices_end() const { return _vertices.end() ; }

		inline edge_iterator       edges_begin() { return _edges.begin() ; }
		inline const_edge_iterator edges_begin() const { return _edges.begin() ; }
		inline edge_iterator       edges_end() { return _edges.end() ; }
		inline const_edge_iterator edges_end() const { return _edges.end() ; }
	private:
		vertex_set _vertices ;
		edge_set   _edges ;

		/**
		 * no copy constructor
		 */
		Graph( const Graph& graph ) ;
	};

} // namespace egraph

#endif
