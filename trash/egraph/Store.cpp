#include <egraph/Store.h>

#include <egraph/helper/ogr.h>

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

    this->dataset = helper::openDataset(path);
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
    return helper::getLayerNames(dataset);
}

///
///
///
std::vector<DefaultVertex> Store::vertices( const std::string& layerName )
{
    OGRLayer *layer = helper::getLayerByName(dataset,layerName);

    int indexId = helper::getFieldIndex(layer, "id", false);
    std::vector<DefaultVertex> vertices;
    vertices.reserve(layer->GetFeatureCount());

    OGRFeature *feature = layer->GetNextFeature();
    while (feature != NULL)
    {
        DefaultVertex vertex;
        vertex.id = (indexId < 0 ) ? feature->GetFID() : feature->GetFieldAsInteger(indexId);
        /* decode geometry */
        {
            OGRGeometry *geometry = feature->GetGeometryRef();
            OGRPoint *p = dynamic_cast<OGRPoint *>(geometry);
            if (p != NULL)
            {
                vertex.geom = Point(p->getX(),p->getY());
            }
        }

        vertices.push_back(vertex);
        feature = layer->GetNextFeature();
    }
    return vertices;
}


///
///
///
std::vector<DefaultEdge> Store::edges(const std::string& layerName)
{
    OGRLayer *layer = this->dataset->GetLayerByName(layerName.c_str());
    if ( layer == NULL ){
        std::ostringstream oss;
        oss << "Layer " << layerName << " not found";
        throw std::runtime_error(oss.str());
    }
    int indexId        = helper::getFieldIndex(layer, "id", false);
    int indexSource    = helper::getFieldIndex(layer, "source");
    int indexTarget    = helper::getFieldIndex(layer, "target");
    int indexDirection = helper::getFieldIndex(layer, "direction", false);

    std::vector<DefaultEdge> edges;
    edges.reserve(layer->GetFeatureCount());

    OGRFeature *feature = layer->GetNextFeature();
    while (feature != NULL)
    {
        DefaultEdge edge;
        edge.id = (indexId < 0 ) ? feature->GetFID() : feature->GetFieldAsInteger(indexId);
        edge.source = feature->GetFieldAsInteger(indexSource);
        edge.target = feature->GetFieldAsInteger(indexTarget);
        if ( indexDirection < 0 ){
            edge.direction = Direction::BOTH;
        }else{
            edge.direction = static_cast<Direction>(feature->GetFieldAsInteger(indexDirection));
        }
        /* decode geometry */
        {
            OGRGeometry *geometry = feature->GetGeometryRef();
            OGRLineString *ls = dynamic_cast<OGRLineString *>(geometry);
            if (ls != NULL)
            {
                edge.geom.reserve(ls->getNumPoints());
                for ( int i = 0; i < ls->getNumPoints(); i++ ){
                    Point point(ls->getX(i),ls->getY(i));
                    edge.geom.push_back(point);
                }
            }
        }

        edges.push_back(edge);
        feature = layer->GetNextFeature();
    }

    return edges;
}

} // namespace egraph