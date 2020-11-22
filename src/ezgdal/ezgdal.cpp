#include <ezgdal/ezgdal.h>

#include <sstream>
#include <exception>

namespace ezgdal {

/**
 * invokes GDALAllRegister on the first call
 */
void ensureGDALIsInitialized(){
    static bool initialized{false};
    if ( ! initialized ){
        GDALAllRegister();
        initialized = true;
    }
}

///
///
///
std::shared_ptr<OGRFeature> makeShared(OGRFeature* feature)
{
    return std::shared_ptr<OGRFeature>(feature,&OGRFeature::DestroyFeature);
}

///
///
///
GDALDatasetUniquePtr openVectorDataset(const std::string& path)
{
    ensureGDALIsInitialized();
    GDALDataset * dataset = (GDALDataset *)GDALOpenEx(path.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (dataset == NULL){
        std::ostringstream oss;
        oss << "Fail to open dataset '" << path << "'" ;
        throw std::runtime_error(oss.str());
    }
    return GDALDatasetUniquePtr(dataset);
}

///
///
///
std::vector<std::string> getLayerNames(GDALDataset* dataset)
{
    std::vector<std::string> result ;

    int layerCount = dataset->GetLayerCount();
    for ( int i = 0; i < layerCount; i++ ){
        OGRLayer *layer = dataset->GetLayer(i);
        result.push_back( layer->GetName() );
    }

    return result;
}

///
///
///
OGRLayer* getLayerByName(GDALDataset* dataset, const std::string & name)
{
    OGRLayer *layer = dataset->GetLayerByName(name.c_str());
    if ( layer == NULL ){
        std::ostringstream oss;
        oss << "Layer '" << name << "' not found";
        throw std::runtime_error(oss.str());
    }
    return layer;
}

///
///
///
int getFieldIndex( OGRLayer *layer, const char* name, bool required )
{
    int index = layer->FindFieldIndex(name,false);
    if ( index < 0 && required ){
        std::ostringstream oss;
        oss << "Required field " << name << " not found (found : ";
        OGRFeatureDefn * def = layer->GetLayerDefn();
        for ( int i = 0; i < def->GetFieldCount(); i++ ){
            if ( i != 0 ){
                oss << ", ";
            }
            oss << "'" << def->GetFieldDefn(i)->GetNameRef() << "'";
        }
        oss << ")";
        throw std::runtime_error(oss.str());
    }
    return index;
}


} // namespace ezgdal
