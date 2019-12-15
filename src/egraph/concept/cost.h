#pragma once

#include <egraph/FeatureGraph.h>

namespace egraph {
namespace concept {

	/**
	 * @brief default cost implementation
	 */
	template < typename Properties >
	inline double cost( const Properties & properties ){
		return properties.cost ;
	}

	/**
	 * @brief cost implementation when cost is the single edge property
	 */
	template <>
	inline double cost( const double & properties ){
		return properties ;
	}

	/**
	 * @brief feature implementation (either "cost" value or geometry length)
	 */
	template <>
	double cost( const FeaturePtr & properties);


} // namespace concept
} // namespace egraph
