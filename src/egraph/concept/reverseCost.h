#pragma once

#include <egraph/FeatureGraph.h>

namespace egraph {
namespace concept {

	/**
	 * @brief default reverseCost implementation
	 */
	template < typename Properties >
	inline double reverseCost( const Properties & properties ){
		return properties.reverseCost ;
	}

	/**
	 * @brief cost implementation when cost is the single edge property
	 */
	template <>
	inline double reverseCost( const double & properties ){
		return properties ;
	}

	/**
	 * @brief feature implementation (either "cost" value or geometry length)
	 */
	template <>
	double reverseCost( const FeaturePtr & properties);


} // namespace concept
} // namespace egraph
