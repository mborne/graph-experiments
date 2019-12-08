#include <egraph/Store.h>

#include <gdal/gdal.h>
#include <gdal/gdal_priv.h>
#include <gdal/gdal_frmts.h>
#include <gdal/ogrsf_frmts.h>
#include <exception>

namespace egraph
{

///
///
///
Store::Store(const char *path)
{
    GDALAllRegister();

    this->dataset = (GDALDataset *)GDALOpenEx(path, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (this->dataset == NULL)
    {
        throw std::runtime_error("fail to open file");
    }
}

///
///
///
Store::~Store()
{
    GDALClose(this->dataset);
}

///
///
///
std::vector<std::string> Store::layerNames()
{
    std::vector<std::string> result ;

    int layerCount = this->dataset->GetLayerCount();
    for ( int i = 0; i < layerCount; i++ ){
        OGRLayer *layer = this->dataset->GetLayer(i);
        result.push_back( layer->GetName() );
    }

    return result;
}

/**
 * Utilitaire pour rechercher les noms de champs
 */
int findFieldIndex( OGRLayer *layer, const char* name, bool required ){
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


///
///
///
std::vector<Edge> Store::edges(const std::string& layerName)
{
    OGRLayer *layer = this->dataset->GetLayerByName(layerName.c_str());
    if ( layer == NULL ){
        std::ostringstream oss;
        oss << "Layer " << layerName << " not found";
        throw std::runtime_error(oss.str());
    }
    int indexId     = findFieldIndex(layer, "id", false);
    int indexSource = findFieldIndex(layer,"source", true);
    int indexTarget = findFieldIndex(layer,"target", true);
    // int indexSens = layer->FindFieldIndex("SENS", false);

    std::vector<Edge> edges;
    edges.reserve(layer->GetFeatureCount());

    OGRFeature *feature = layer->GetNextFeature();
    while (feature != NULL)
    {
        Edge edge;
        edge.id = (indexId < 0 ) ? feature->GetFID() : feature->GetFieldAsInteger(indexId);
        edge.source = feature->GetFieldAsInteger(indexSource);
        edge.target = feature->GetFieldAsInteger(indexTarget);

        // // sens
        // road.setDirection(decodeSens(feature->GetFieldAsString(indexSens)));
        // // geometry
        // OGRGeometry *geometry = feature->GetGeometryRef();
        // OGRLineString *ls = dynamic_cast<OGRLineString *>(geometry);
        // if (ls != NULL)
        // {
        //     LineString geometry;
        //     geometry.reserve(ls->getNumPoints());
        //     for ( int i = 0; i < ls->getNumPoints(); i++ ){
        //         Coordinate coordinate = {ls->getX(i),ls->getY(i)};
        //         geometry.push_back(coordinate);
        //     }
        //     road.setGeometry(geometry);
        // }

        edges.push_back(edge);
        feature = layer->GetNextFeature();
    }

    return edges;
}

} // namespace egraph