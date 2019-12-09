#ifndef _EGRAPH_VERTEX_H_
#define _EGRAPH_VERTEX_H_

#include <set>

namespace egraph {

	/**
	 * @brief graph
	 */
	template < typename Graph >
	class Vertex {
		template<typename> friend class Edge ;
	public:
		typedef typename Graph::vertex_handle      vertex_handle ;
		typedef typename Graph::edge_handle        edge_handle ;
		typedef typename Graph::directed_edge      directed_edge ;
		typedef typename Graph::vertex_properties  properties_t ;

		typedef std::set< edge_handle >            edge_set ;
		typedef typename edge_set::iterator        edge_iterator ;
		typedef typename edge_set::const_iterator  const_edge_iterator ;

		/**
		 * @brief constructor with a source and a target
		 */
		Vertex( const properties_t& properties = properties_t() ):
			_properties(properties),
			_inEdges(),
			_outEdges()
		{

		}

		~Vertex()
		{
			_inEdges.clear() ;
			_outEdges.clear() ;
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

		/**
		 * @brief get in degree
		 */
		inline size_t inDegree() const {
			return _inEdges.size();
		}
		/**
		 * @brief get out degree
		 */
		inline size_t outDegree() const {
			return _outEdges.size();
		}
		/**
		 * @brief get out degree
		 */
		inline size_t degree() const {
			return inDegree() + outDegree() ;
		}

		/**
		 * @brief get incident edges
		 */
		std::vector< directed_edge > incidentEdges() const {
			std::vector< directed_edge > result;
			for ( const_edge_iterator it = in_edges_begin(); it != in_edges_end(); ++it ){
				result.push_back( directed_edge( *it, INVERSE ) ) ;
			}
			for ( const_edge_iterator it = out_edges_begin(); it != out_edges_end(); ++it ){
				result.push_back( directed_edge( *it, DIRECT ) ) ;
			}
			return result ;
		}


		inline edge_iterator       in_edges_begin() { return _inEdges.begin(); }
		inline const_edge_iterator in_edges_begin() const { return _inEdges.begin(); }
		inline edge_iterator       in_edges_end() { return _inEdges.end(); }
		inline const_edge_iterator in_edges_end() const { return _inEdges.end(); }

		inline edge_iterator       out_edges_begin() { return _outEdges.begin(); }
		inline const_edge_iterator out_edges_begin() const { return _outEdges.begin(); }
		inline edge_iterator       out_edges_end() { return _outEdges.end(); }
		inline const_edge_iterator out_edges_end() const { return _outEdges.end(); }


	private:
		properties_t  _properties ;

		/**
		 * @brief index on in edges (managed by Edge)
		 */
		std::set< edge_handle > _inEdges ;
		/**
		 * @brief index on out edges (managed by Edge)
		 */
		std::set< edge_handle > _outEdges ;
	};

} // namespace egraph

#endif
