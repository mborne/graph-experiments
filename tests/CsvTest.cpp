#define BOOST_TEST_MODULE CsvTest
#include <boost/test/unit_test.hpp>

#include <egraph/helper/csv.h>

using namespace egraph ;

BOOST_AUTO_TEST_SUITE( CsvTest )

BOOST_AUTO_TEST_CASE( testEscapeCSV )
{
    BOOST_CHECK_EQUAL("test",helper::escapeCSV("test"));
    BOOST_CHECK_EQUAL("\"a,b\"",helper::escapeCSV("a,b"));
    BOOST_CHECK_EQUAL("\"Tu dis \"\"quoi\"\"?\"",helper::escapeCSV("Tu dis \"quoi\"?"));
}

BOOST_AUTO_TEST_SUITE_END()
