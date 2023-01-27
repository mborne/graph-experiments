#include <egraph/concept/wkt.h>

#include <ogrsf_frmts.h>

namespace egraph {
namespace concept {

///
///
///
template <>
std::string wkt( const FeaturePtr & properties)
{

    OGRGeometry* geometry = properties->GetGeometryRef();
    if ( geometry != NULL ){
        char* wkt;
        geometry->exportToWkt(&wkt);
        std::string result(wkt);
        CPLFree(wkt);
        return result;
    }else{
        return "GEOMETRYCOLLECTION EMPTY";
    }
}


} // namespace concept
} // namespace egraph
