#include <iostream>

#include <vector>

#include <boost/progress.hpp>

#include <egraph/Graph.h>
#include <egraph/algorithm/ShortestPathTree.h>
#include <egraph/algorithm/ShortestPathTreeBuilder.h>

#include <boost/timer.hpp>

using namespace egraph ;

int main( int argc, char* argv[] ){
	typedef Graph< int, double > graph_t ;

	graph_t g ;

	std::vector< graph_t::vertex_handle > vertices ;

	const int N = 1000000 ;
	boost::progress_display display( N );
	for ( int i = 0; i < N; i++ ){
		vertices.push_back( g.addVertex( i ) ) ;
		if ( i != 0 ){
			g.addEdge( vertices[i-1], vertices[i], 2.5*i );
		}
		++display ;
	}

	for ( graph_t::const_vertex_iterator it = g.vertices_begin(); it != g.vertices_end(); ++it ){
		graph_t::vertex_handle h = *it ;
	//	std::cout << "v " << h->properties() << " (" << h->inDegree() << "," << h->outDegree() << ")" << std::endl;
	}

	for ( graph_t::const_edge_iterator it = g.edges_begin(); it != g.edges_end(); ++it ){
		graph_t::edge_handle h = *it ;
	//	std::cout << "e " << h->properties() << std::endl ;
	}


	std::cout << "building tree..." << std::endl ;
	algorithm::ShortestPathTreeBuilder< graph_t > treeBuilder( g );
	treeBuilder.setTargetVertex( vertices[20] ) ;
	treeBuilder.buildTree( vertices[1] );

	std::vector< graph_t::directed_edge > path = treeBuilder.tree().path( vertices[20] ) ;
	for ( size_t i = 0; i < path.size(); i++ ){
		std::cout << "(" << path[i].source() << " => " << path[i].target()  << ")" << std::endl ;
	}

	return 0 ;
}
