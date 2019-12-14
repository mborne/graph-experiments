#pragma once

#include <iostream>

#include <boost/graph/graph_traits.hpp>
#include <egraph/routing/PathTreeNode.h>

#include <map>
#include <algorithm>
#include <limits>

#include <boost/assert.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

namespace egraph
{
namespace routing
{

/**
 * @brief builds a shortest path tree
 */
template <typename G>
class PathTree
{
public:
	typedef typename boost::graph_traits<G>::vertex_descriptor vertex_descriptor;
	typedef typename boost::graph_traits<G>::edge_descriptor edge_descriptor;

	typedef PathTreeNode<G> node_type;

	/**
	 * A set of nodes indexed according "node.visited"
	 */
	typedef typename boost::multi_index_container<
		node_type,
		boost::multi_index::indexed_by<
			// sort by item::operator<
			boost::multi_index::ordered_unique<boost::multi_index::identity<node_type>>,
			// sort by less<bool> on visited
			boost::multi_index::ordered_non_unique<boost::multi_index::member<node_type, bool, &node_type::visited>>
		>
	> node_set;

	typedef typename node_set::template nth_index<0>::type reached_index_t;
	typedef typename reached_index_t::iterator             reached_iterator;
	typedef typename reached_index_t::const_iterator       const_reached_iterator;

	typedef typename node_set::template nth_index<1>::type visited_index_t;
	typedef typename visited_index_t::iterator             not_visited_iterator;
	typedef typename visited_index_t::const_iterator       const_not_visited_iterator;

	/**
	 * @brief constructor with a graph
	 */
	PathTree(const G &graph):
		_graph(graph)
	{
	}

	/**
	 * @brief retrieve graph
	 */
	const G &graph() const
	{
		return _graph;
	}

	/**
	 * @brief mark the vertex as reached with a cost
	 */
	void setRoot(vertex_descriptor root)
	{
		_nodes.clear();
		_nodes.insert(node_type(root, 0.0));
	}

	/**
	 * @brief get the path to a vertex (empty is not reached)
	 */
	std::vector<edge_descriptor> path(vertex_descriptor destination) const
	{
		std::vector<edge_descriptor> result;
		if ( ! isReached(destination) ){
			return result;
		}

		node_type current = node(destination);
		while ( ! current.isRoot() ){
			edge_descriptor edge = current.reachingEdge.get();
			result.push_back(edge);

			vertex_descriptor source = boost::source(edge,_graph);
			vertex_descriptor target = boost::target(edge,_graph);
			if ( current.vertex == source ){
				current = node(target);
			}else{
				current = node(source);
			}
		}

		std::reverse(result.begin(), result.end());
		return result;
	}

	/**
	 * @brief indicates if a vertex is reached
	 */
	inline bool isReached(vertex_descriptor vertex) const
	{
		return _nodes.find(vertex) != _nodes.end();
	}

	/**
	 * @brief get a vertex node
	 *
	 * @warning the vertex must be reached
	 */
	const node_type &node(vertex_descriptor vertex) const
	{
		reached_iterator it = _nodes.template get<0>().find(vertex);
		BOOST_ASSERT(it != _nodes.end());
		return *it;
	}

	/**
	 * @brief add a vertex node
	 */
	void setNode(node_type node)
	{
		reached_iterator it = _nodes.template get<0>().find(node.vertex);
		if (it != _nodes.template get<0>().end())
		{
			_nodes.replace(it, node);
		}
		else
		{
			_nodes.insert(node);
		}
	}

	inline reached_iterator reached_begin()
	{
		return _nodes.template get<0>().begin();
	}
	inline const_reached_iterator reached_begin() const
	{
		return _nodes.template get<0>().begin();
	}

	inline reached_iterator reached_end()
	{
		return _nodes.template get<0>().end();
	}
	inline const_reached_iterator reached_end() const
	{
		return _nodes.template get<0>().end();
	}

	inline not_visited_iterator not_visited_begin()
	{
		return _nodes.template get<1>().lower_bound(false);
	}
	inline const_not_visited_iterator not_visited_begin() const
	{
		return _nodes.template get<1>().lower_bound(false);
	}

	inline not_visited_iterator not_visited_end()
	{
		return _nodes.template get<1>().upper_bound(false);
	}
	inline const_not_visited_iterator not_visited_end() const
	{
		return _nodes.template get<1>().upper_bound(false);
	}

private:
	const G &_graph;
	/**
	 * @brief store reached vertices
	 */
	node_set _nodes;
};

} // namespace routing
} // namespace egraph
