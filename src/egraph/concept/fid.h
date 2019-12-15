#pragma once

#include <egraph/FeatureGraph.h>

namespace egraph {
namespace concept {

	/**
	 * @brief feature identifier for vertex/edge properties
	 */
	template < typename Properties >
	inline int fid( const Properties & properties ){
		return properties.id ;
	}

	/**
	 * @brief feature identifier when it is the single property
	 */
	template <>
	inline int fid( const int & properties ){
		return properties ;
	}

	/**
	 * @brief feature implementation (feature->GetFID())
	 */
	template <>
	int fid( const FeaturePtr & properties);


} // namespace concept
} // namespace egraph
