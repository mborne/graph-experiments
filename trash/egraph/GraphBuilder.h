#pragma once

#include <boost/assert.hpp>
#include <map>
#include <egraph/DefaultGraph.h>

namespace egraph {

    class GraphBuilder {
    public:
        typedef typename DefaultGraph::vertex_descriptor vertex_descriptor;
        typedef typename DefaultGraph::edge_descriptor   edge_descriptor;

        GraphBuilder(DefaultGraph & graph):
            _graph(graph)
        {
            DefaultGraph::vertex_iterator it,end;
            for ( boost::tie(it,end) = boost::vertices(_graph); it != end; ++it ){
                const DefaultVertex & v = _graph[*it];
                _mapVertices.insert(std::make_pair(v.id,*it));
            }
        }

        /**
         * Create or set vertex property returning descriptor
         */
        vertex_descriptor addVertex(const DefaultVertex & vertex){
            auto it = _mapVertices.find(vertex.id);
            if ( it != _mapVertices.end() ){
                vertex_descriptor v = it->second;
                _graph[v] = vertex;
                return v;
            }else{
                vertex_descriptor v = boost::add_vertex(vertex,_graph);
                _mapVertices.insert( std::make_pair(vertex.id,v) );
                return v;
            }
        }

        /**
         * Add edge to the graph
         */
        edge_descriptor addEdge(const DefaultEdge& edge){
            return boost::add_edge(
                findVertexDescriptor(edge.source),
                findVertexDescriptor(edge.target),
                edge,
                _graph
            ).first;
        }

    private:
        DefaultGraph & _graph;
        std::map<int, vertex_descriptor> _mapVertices;

        vertex_descriptor findVertexDescriptor(int id){
            auto it = _mapVertices.find(id);
            BOOST_ASSERT(it != _mapVertices.end());
            return it->second;
        }
    };

}