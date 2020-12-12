#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <fstream>
#include <chrono>

#include <egraph/LoaderParams.h>
#include <egraph/Loader.h>
#include <egraph/routing/PathTreeBuilder.h>

#include <egraph/helper/csv.h>

#define NUM_TREES 20

using namespace egraph;
using namespace egraph::routing;

int main(int argc, char* argv[]){
    LoaderParams loaderParams;
    {
        po::options_description desc("Usage : command/snowplow <output>");
        desc.add_options()
            ("help", "produce help message")
            /* input data */
            (
                "input",
                po::value<std::string>(&loaderParams.inputPath)->default_value(loaderParams.inputPath),
                "Input OGR dataset"
            )
            (
                "layer-vertex",
                po::value<std::string>(&loaderParams.vertexLayerName)->default_value(loaderParams.vertexLayerName),
                "Vertex layer name"
            )
            (
                "layer-edge",
                po::value<std::string>(&loaderParams.edgeLayerName)->default_value(loaderParams.edgeLayerName),
                "Edge layer name (ex : edge_distance_weighted, edge_time_weighted)"
            )
        ;
        /* define positional options */
        po::positional_options_description pDesc;

        /* parse command line */
        try {
            po::variables_map vm;
            po::store(po::command_line_parser(argc, argv).
            options(desc).positional(pDesc).run(), vm);
            po::notify(vm);

            if (vm.count("help"))
            {
                std::cout << desc << std::endl;
                return 0;
            }
        }catch(std::exception& e){
            std::cerr << "ERROR : " << e.what() << std::endl;
            std::cerr << desc << std::endl;
            return 1;
        }
    }

    /* load a FeatureGraph with GDAL/OGR */
    std::cout << "Load graph vertex_layer=" << loaderParams.vertexLayerName << " edge_layer=" << loaderParams.edgeLayerName << " ..." << std::endl;
    FeatureGraphLoader loader(loaderParams.inputPath);
    FeatureGraph graph = loader.getFeatureGraph(
        loaderParams.vertexLayerName,
        loaderParams.edgeLayerName
    );

    /* display the number of vertices */
    std::cout << "FeatureGraph loaded (num_vertices=" << boost::num_vertices(graph) << ", num_edges=" << boost::num_edges(graph) << ")" << std::endl;

    /* build path trees for some vertex */
    {
        int count = 0;
        for (
            auto [it,end] = boost::vertices(graph);
            it != end && count < NUM_TREES;
            ++it, ++count
        ){
            FeatureGraph::vertex_descriptor origin = *it;
            int originId = concept::fid( graph[origin] );
            std::cout << "Create PathTree from " << originId << "..." << std::endl;

            auto startTime = std::chrono::system_clock::now();
            PathTree<FeatureGraph> pathTree(graph);
            pathTree.setRoot(origin);
            PathTreeBuilder<FeatureGraph> pathTreeBuilder(pathTree);
            pathTreeBuilder.build();

            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now()-startTime
            );
            std::cout << "PathTree created from " << originId << " in " << elapsedTime.count() << "s" << std::endl;

            std::string ofsName("distance-from-");
            ofsName += std::to_string(originId);
            ofsName += ".csv";
            std::cout << "save PathTree to " << ofsName << std::endl;
            std::ofstream ofs(ofsName.c_str());
            helper::pathTreeToCSV(ofs,pathTree);
        }
    }

}
