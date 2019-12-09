#pragma once

#include <string>
#include <vector>

class GDALDataset;
class OGRLayer;

namespace egraph {
    namespace helper {

        /**
         * Open dataset throwing on failure
         */
        GDALDataset* openDataset(const std::string& path);

        /**
         * Get layer names from dataset
         */
        std::vector<std::string> getLayerNames(GDALDataset* dataset);

        /**
         * Get layer by name throwing on failure
         */
        OGRLayer* getLayerByName(GDALDataset* dataset, const std::string & name);

        /**
         * Get field index from a layer
         */
        int getFieldIndex( OGRLayer *layer, const char* name, bool required = true );
    }
}