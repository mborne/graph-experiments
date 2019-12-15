#pragma once

#include <string>
#include <egraph/FeatureGraph.h>

class GDALDataset;
class OGRLayer;

namespace egraph {

    /**
     * @brief Load FeatureGraph relying on GDAL/OGR
     */
    class FeatureGraphLoader {
    public:
        FeatureGraphLoader(
            const std::string& path = "PG:dbname=gis",
            const std::string& vertexLayerName = "graph.vertex",
            const std::string& edgeLayerName = "graph.edge"
        );

        ~FeatureGraphLoader();

        /**
         * Load FeatureGraph from dataset
         */
        FeatureGraph getFeatureGraph() const ;

    private:
        GDALDataset * dataset ;
        OGRLayer* vertexLayer ;
        OGRLayer* edgeLayer ;
    };

}
