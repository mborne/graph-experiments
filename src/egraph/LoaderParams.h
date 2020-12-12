#pragma once

#include <string>

namespace egraph {
    /**
     * @brief Loader config with default params
     */
    struct LoaderParams {
        std::string inputPath{"PG:dbname=gis active_schema=roadgraph"};
        std::string vertexLayerName{"vertex"};
        std::string edgeLayerName{"edge"};
    };
}
