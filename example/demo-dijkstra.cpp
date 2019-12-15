#include <iostream>

#include <vector>

#include <boost/progress.hpp>

#include <egraph/Graph.h>
#include <egraph/routing/PathTreeBuilder.h>

#include <boost/timer.hpp>

using namespace egraph ;
using namespace egraph::routing ;

int main( int argc, char* argv[] ){
	typedef Graph< int, double >  graph_type ;
	typedef graph_type::vertex_descriptor vertex_descriptor;
	typedef graph_type::edge_descriptor   edge_descriptor;

	graph_type g ;

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
	vertex_descriptor origin = vertices[1];
	PathTree<graph_type> pathTree(g);
	pathTree.setRoot(origin);
	PathTreeBuilder<graph_type> builder(pathTree);
	builder.build();

	/* retreive path */
	vertex_descriptor destination = vertices[20] ;
	std::vector< edge_descriptor > path = pathTree.path( destination ) ;

	/* display path */
	{
		vertex_descriptor last = origin;
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
