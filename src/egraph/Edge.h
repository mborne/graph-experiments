#ifndef _EGRAPH_EDGE_H_
#define _EGRAPH_EDGE_H_

#include <cassert>

namespace egraph {

	/**
	 * @brief graph
	 */
	template < typename Graph >
	class Edge {
	public:
		typedef typename Graph::vertex_handle      vertex_handle ;
		typedef typename Graph::edge_handle        edge_handle ;
		typedef typename Graph::edge_properties    properties_t ;

		/**
		 * @brief constructor with a source and a target
		 */
		Edge( vertex_handle source, vertex_handle target, const properties_t& properties = properties_t() ):
			_source(NULL),
			_target(NULL),
			_properties(properties)
		{
			assert( source != NULL );
			assert( target != NULL );

			setSource(source);
			setTarget(target);
		}
		/**
		 * @brief destructor
		 */
		~Edge()
		{
			_source->_outEdges.erase( this );
			_target->_inEdges.erase( this );
		}

		/**
		 * @brief get source vertex
		 */
		vertex_handle source() const {
			return _source ;
		}
		/**
		 * @brief get source vertex
		 */
		void setSource( vertex_handle source ){
			if ( _source != NULL ){
				_source->_outEdges.erase( this );
			}
			_source = source ;
			_source->_outEdges.insert( this );
		}
		/**
		 * @brief get target vertex
		 */
		vertex_handle target() const {
			return _target ;
		}
		/**
		 * @brief get source vertex
		 */
		void setTarget( vertex_handle target ) {
			if ( _target != NULL ){
				_target->_inEdges.erase( this );
			}
			_target = target ;
			_target->_inEdges.insert( this );
		}

		/**
		 * @brief get vertex properties
		 */
		const properties_t & properties() const {
			return _properties ;
		}
		/**
		 * @brief get vertex properties
		 */
		void setProperties( const properties_t & properties ) const {
			_properties = properties ;
		}

	private:
		vertex_handle _source ;
		vertex_handle _target ;
		properties_t  _properties ;

		/**
		 * @brief no copy constructor
		 */
		Edge( const Edge& edge ) ;
	};

} // namespace egraph

#endif
