#include <iostream>

#include <vector>

#include <boost/progress.hpp>

#include <egraph/Graph.h>
#include <egraph/algorithm/ShortestPathTree.h>
#include <egraph/algorithm/ShortestPathTreeBuilder.h>

#include <boost/timer.hpp>

using namespace egraph ;

int main( int argc, char* argv[] ){
	typedef Graph< int, double >  graph_t ;
	typedef graph_t::vertex_descriptor vertex_descriptor;
	typedef graph_t::edge_descriptor   edge_descriptor;

	graph_t g ;

	std::vector< vertex_descriptor > vertices ;

	const int N = 1000000 ;
	boost::progress_display display( N );
	for ( int i = 0; i < N; i++ ){
		vertices.push_back( boost::add_vertex(i,g) ) ;
		if ( i != 0 ){
			boost::add_edge(vertices[i-1], vertices[i], 2.5*i,g);
		}
		++display ;
	}


	std::cout << "building tree..." << std::endl ;
	algorithm::ShortestPathTreeBuilder< graph_t > treeBuilder( g );
	treeBuilder.setTargetVertex( vertices[20] ) ;
	treeBuilder.buildTree( vertices[1] );

	/* find path */
	vertex_descriptor root = vertices[20];
	std::vector< edge_descriptor > path = treeBuilder.tree().path( root ) ;

	/* display path */
	{
		vertex_descriptor last = root;
		for ( const edge_descriptor & e : path ){
			if ( last == boost::source(e,g) ){
				std::cout << "(" << boost::source(e,g) << " -> " << boost::target(e,g)  << ")" << std::endl ;
				last = boost::target(e,g);
			}else{
				std::cout << "(" << boost::target(e,g) << " -> " << boost::source(e,g)  << ")" << std::endl ;
				last = boost::source(e,g);
			}
		}
	}

	return 0 ;
}
