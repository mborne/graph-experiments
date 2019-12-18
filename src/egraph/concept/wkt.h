#pragma once

#include <egraph/FeatureGraph.h>

namespace egraph {
namespace concept {

	/**
	 * @brief default cost implementation
	 */
	template < typename Properties >
	inline std::string wkt( const Properties & properties ){
		return "GEOMETRYCOLLECTION EMPTY" ;
	}

	/**
	 * @brief feature implementation
	 */
	template <>
	std::string wkt( const FeaturePtr & properties);

} // namespace concept
} // namespace egraph
