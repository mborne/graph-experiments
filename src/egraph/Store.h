#pragma once

#include <egraph/Edge.h>

#include <string>

// declare GDAL class
class GDALDataset;

namespace egraph {

    /**
     * Représente une source de données à partir de laquelle
     * on peut télécharger des données
     */
    class Store {
    public:
        Store(const char* path);
        ~Store();

        /**
         * Récupération de la liste des couches
         */
        std::vector<std::string> layerNames();

        std::vector<Edge> edges( const std::string& layerName = "edge" ) ;
    private:
        GDALDataset * dataset;
    };

}