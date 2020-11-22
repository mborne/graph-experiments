#include <boost/test/unit_test.hpp>

#include <ezgdal/ezgdal.h>

#include "../test_config.h"

BOOST_AUTO_TEST_SUITE( EzgdalRegressTest )

BOOST_AUTO_TEST_CASE( testReadPlaces )
{
    std::string path = TEST_DIR+"/ezgdal/data";

    /* test openVectorDataset */
    GDALDatasetUniquePtr dataset = ezgdal::openVectorDataset(path);
    BOOST_REQUIRE(dataset.get() != nullptr);

    /* test getLayerNames */
    {
        std::vector< std::string > layerNames = ezgdal::getLayerNames(dataset.get());
        BOOST_CHECK_EQUAL(1,layerNames.size());
        BOOST_CHECK_EQUAL("sample",layerNames[0]);
    }

    /* test getLayerByName */
    {
        OGRLayer* layer = ezgdal::getLayerByName(dataset.get(),"sample");
        BOOST_REQUIRE_EQUAL(2,layer->GetFeatureCount());

        int indexName = ezgdal::getFieldIndex(layer,"name",false);
        BOOST_REQUIRE(indexName != -1);

        BOOST_TEST_MESSAGE("check hability to read WKT as geometry");
        {
            OGRFeatureUniquePtr feature{layer->GetNextFeature()};
            BOOST_CHECK_EQUAL(1,feature->GetFID());
            BOOST_CHECK_EQUAL(std::string("Point 1"),feature->GetFieldAsString(indexName));
            OGRGeometry* geom = feature->GetGeometryRef();
            BOOST_REQUIRE(geom != nullptr);
            OGRPoint* point = dynamic_cast<OGRPoint*>(geom);
            BOOST_REQUIRE(point != nullptr);
            BOOST_CHECK_EQUAL(5.0,point->getX());
            BOOST_CHECK_EQUAL(44.0,point->getY());
        }
        {
            OGRFeatureUniquePtr feature{layer->GetNextFeature()};
            BOOST_CHECK_EQUAL(2,feature->GetFID());
            BOOST_CHECK_EQUAL(std::string("LineString 1"),feature->GetFieldAsString(indexName));
            OGRGeometry* geom = feature->GetGeometryRef();
            BOOST_CHECK(geom != nullptr);
            OGRLineString* lineString = dynamic_cast<OGRLineString*>(geom);
            BOOST_REQUIRE(lineString != nullptr);
            BOOST_REQUIRE_EQUAL(2,lineString->getNumPoints());
            OGRPoint point;
            // check first point
            lineString->getPoint(0,&point);
            BOOST_CHECK_EQUAL(5.0,point.getX());
            BOOST_CHECK_EQUAL(44.0,point.getY());
            // check second point
            lineString->getPoint(1,&point);
            BOOST_CHECK_EQUAL(6.0,point.getX());
            BOOST_CHECK_EQUAL(45.0,point.getY());
        }

    }


}


BOOST_AUTO_TEST_SUITE_END()
