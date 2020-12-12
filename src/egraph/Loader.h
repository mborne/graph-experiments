#pragma once

#include <string>
#include <egraph/FeatureGraph.h>
#include <ezgdal/ezgdal.h>

namespace egraph {

    /**
     * @brief Load FeatureGraph relying on GDAL/OGR
     */
    class FeatureGraphLoader {
    public:
        FeatureGraphLoader(
            const std::string& path = "PG:dbname=gis active_schema=roadgraph"
        );

        FeatureGraphLoader( const FeatureGraphLoader & other ) = delete;

        ~FeatureGraphLoader() = default;

        /**
         * Load FeatureGraph from dataset
         */
        FeatureGraph getFeatureGraph(
            const std::string& vertexLayerName = "vertex",
            const std::string& edgeLayerName = "edge"
        ) const ;

    private:
        GDALDatasetUniquePtr dataset ;
    };

}
