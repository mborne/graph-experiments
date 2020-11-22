#pragma once

#include <egraph/Graph.h>

typedef egraph::Graph<std::string,double> TestGraph;

/**
 * @brief find vertex by name
 */
TestGraph::vertex_descriptor findVertex( const std::string & name, const TestGraph & g );

TestGraph createSampleGraphA();

/**
 * A -> B, A -> C, B -> C
 */
TestGraph createSampleGraphB();
