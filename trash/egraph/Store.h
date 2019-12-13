#pragma once

#include <string>
#include <egraph/DefaultVertex.h>
#include <egraph/DefaultEdge.h>

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

        /**
         * Récupération des arcs à partir d'une table
         */
        std::vector<DefaultVertex> vertices( const std::string& layerName = "vertex" ) ;

        /**
         * Récupération des arcs à partir d'une table
         */
        std::vector<DefaultEdge> edges( const std::string& layerName = "edge" ) ;

    private:
        GDALDataset * dataset;
    };

}