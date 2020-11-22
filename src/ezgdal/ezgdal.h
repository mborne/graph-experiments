#ifndef _EZGDAL_EZGDAL_H_
#define _EZGDAL_EZGDAL_H_

#include <string>
#include <vector>

#include <gdal/ogrsf_frmts.h>

namespace ezgdal {

    /**
     * @brief Create a shared pointer that invokes DestroyFeature
     */
    std::shared_ptr<OGRFeature> makeShared(OGRFeature* feature);

    /**
     * @brief Open a vector dataset, throw runtime_error on failure
     */
    GDALDatasetUniquePtr openVectorDataset(const std::string& path);

    /**
     * @brief Get layer names from a dataset
     */
    std::vector<std::string> getLayerNames(GDALDataset* dataset);

    /**
     * @brief Get layer by name throwing on failure
     */
    OGRLayer* getLayerByName(GDALDataset* dataset, const std::string & name);

    /**
     * Get field index from a layer
     */
    int getFieldIndex( OGRLayer *layer, const char* name, bool required = true );

}

#endif
