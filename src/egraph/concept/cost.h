#ifndef _EGRAPH_CONCEPT_COST_H_
#define _EGRAPH_CONCEPT_COST_H_

namespace egraph {
namespace concept {

	/**
	 * @brief default weight getter implementation
	 */
	template < typename Properties >
	double cost( const Properties & properties ){
		return properties.cost ;
	}
	/**
	 * @brief default weight getter implementation
	 */
	template <>
	double cost( const double & properties ){
		return properties ;
	}

} // namespace concept
} // namespace egraph

#endif

