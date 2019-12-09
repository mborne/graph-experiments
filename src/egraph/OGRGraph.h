#pragma once

#include <string>
#include <boost/graph/adjacency_list.hpp>

class GDALDataset;
class OGRLayer;
class OGRFeature;

namespace egraph {

    typedef OGRFeature* OGRFeaturePtr;

    using OGRFeatureGraph = boost::adjacency_list<
        boost::listS,              /* stable identifiers */
        boost::listS,              /* parallel edges allowed + stable identifiers */
        boost::bidirectionalS,
        OGRFeaturePtr,             /* vertex properties */
        OGRFeaturePtr              /* edge properties */
    >;

    /**
     * Un graphe où les listes de sommet et d'arc sont des OGRLayer
     */
    class OGRGraph {
    public:
        OGRGraph(
            const std::string& path = "PG:dbname=gis",
            const std::string& vertexLayerName = "graph.vertex",
            const std::string& edgeLayerName = "graph.edge"
        );

        ~OGRGraph();

        /**
         * Get number of vertices
         */
        int getNumVertices() const ;

        /**
         * Get number of edges
         */
        int getNumEdges() const ;

        /**
         * Load OGRFeatureGraph from dataset
         */
        OGRFeatureGraph getFeatureGraph() const ;

    private:
        GDALDataset * dataset ;
        OGRLayer* vertexLayer ;
        OGRLayer* edgeLayer ;
    };

}
