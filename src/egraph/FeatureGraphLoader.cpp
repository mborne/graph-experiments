#include <egraph/FeatureGraphLoader.h>

#include <ezgdal/ezgdal.h>

#include <gdal/ogrsf_frmts.h>

#include <sstream>
#include <exception>

namespace egraph {

///
///
///
FeatureGraphLoader::FeatureGraphLoader(
    const std::string& path
)
{
    this->dataset = ezgdal::openVectorDataset(path);
}

///
///
///
FeatureGraph FeatureGraphLoader::getFeatureGraph(
    const std::string& vertexLayerName,
    const std::string& edgeLayerName
) const
{
    typedef FeatureGraph::vertex_descriptor vertex_descriptor;

    FeatureGraph graph;

    std::map< int, vertex_descriptor > mapVertices;
    /* read vertices */
    {
        OGRLayer* vertexLayer = ezgdal::getLayerByName(dataset.get(),vertexLayerName);
        for (
            OGRFeatureUniquePtr feature{vertexLayer->GetNextFeature()};
            feature.get() != nullptr;
            feature = OGRFeatureUniquePtr{vertexLayer->GetNextFeature()}
        ){
            int id = feature->GetFID();
            vertex_descriptor vertex = boost::add_vertex(
                ezgdal::makeShared(feature.release()),
                graph
            );
            mapVertices.insert(std::make_pair(id,vertex));
        }
    }
    /* read edges */
    OGRLayer* edgeLayer   = ezgdal::getLayerByName(dataset.get(),edgeLayerName);
    int indexSource = ezgdal::getFieldIndex(edgeLayer,"source");
    int indexTarget = ezgdal::getFieldIndex(edgeLayer,"target");
    for (
        OGRFeatureUniquePtr feature{edgeLayer->GetNextFeature()};
        feature.get() != nullptr;
        feature = OGRFeatureUniquePtr{edgeLayer->GetNextFeature()}
    ){
        /* retreive source by id */
        vertex_descriptor source ;
        {
            auto it = mapVertices.find(feature->GetFieldAsInteger(indexSource));
            if ( it == mapVertices.end() ){
                throw std::runtime_error("source vertex not found");
            }
            source = it->second;
        }
        /* retreive target by id */
        vertex_descriptor target ;
        {
            auto it = mapVertices.find(feature->GetFieldAsInteger(indexTarget));
            if ( it == mapVertices.end() ){
                throw std::runtime_error("target vertex not found");
            }
            target = it->second;
        }
        boost::add_edge(
            source,
            target,
            ezgdal::makeShared(feature.release()),
            graph
        );
    }

    return graph;
}

} // namespace egraph
