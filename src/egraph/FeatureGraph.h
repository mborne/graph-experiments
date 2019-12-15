#pragma once

#include <egraph/Graph.h>

/**
 * @brief declare OGRFeature (include <gdal/ogrsf_frmts.h>)
 */
class OGRFeature;

namespace egraph {

    typedef OGRFeature* FeaturePtr;

    /**
     * @brief a Graph where vertex and edges are OGR features
     */
    using FeatureGraph = Graph<
        FeaturePtr,  /* vertex properties */
        FeaturePtr   /* edge properties */
    >;

} // namespace egraph

