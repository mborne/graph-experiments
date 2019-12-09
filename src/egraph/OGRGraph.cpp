#include <egraph/OGRGraph.h>

#include <egraph/helper/ogr.h>

#include <gdal/ogrsf_frmts.h>

#include <sstream>
#include <exception>

namespace egraph {

///
///
///
OGRGraph::OGRGraph(
    const std::string& path,
    const std::string& vertexLayerName,
    const std::string& edgeLayerName
)
{
    this->dataset     = helper::openDataset(path);
    this->vertexLayer = helper::getLayerByName(this->dataset,vertexLayerName);
    this->edgeLayer   = helper::getLayerByName(this->dataset,edgeLayerName);
}

///
///
///
OGRGraph::~OGRGraph()
{
    GDALClose(this->dataset);
}

///
///
///
int OGRGraph::getNumVertices() const
{
    return this->vertexLayer->GetFeatureCount();
}

///
///
///
int OGRGraph::getNumEdges() const 
{
    return this->edgeLayer->GetFeatureCount();
}

///
///
///
OGRFeatureGraph OGRGraph::getFeatureGraph() const
{
    typedef OGRFeatureGraph::vertex_descriptor vertex_descriptor;

    OGRFeatureGraph graph;

    std::map< int, vertex_descriptor > mapVertices;
    /* read vertices */
    {
        OGRFeature *feature = vertexLayer->GetNextFeature();
        while (feature != NULL){
            int id = feature->GetFID();
            vertex_descriptor vertex = boost::add_vertex(feature,graph);
            mapVertices.insert(std::make_pair(id,vertex));
            feature = vertexLayer->GetNextFeature();
        }
    }
    /* read edges */
    int indexSource = helper::getFieldIndex(edgeLayer,"source");
    int indexTarget = helper::getFieldIndex(edgeLayer,"target");
    {
        OGRFeature *feature = edgeLayer->GetNextFeature();
        while (feature != NULL){
            // read source
            vertex_descriptor source ;
            {
                auto it = mapVertices.find(feature->GetFieldAsInteger(indexSource));
                if ( it == mapVertices.end() ){
                    throw std::runtime_error("source vertex not found");
                }
                source = it->second;
            }
            // read target
            vertex_descriptor target ;
            {
                auto it = mapVertices.find(feature->GetFieldAsInteger(indexTarget));
                if ( it == mapVertices.end() ){
                    throw std::runtime_error("target vertex not found");
                }
                target = it->second;
            }
            boost::add_edge(source,target,feature,graph);

            feature = edgeLayer->GetNextFeature();
        }
    }

    return graph;
}

} // namespace egraph
