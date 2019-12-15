#include <egraph/concept/cost.h>

#include <gdal/ogrsf_frmts.h>

namespace egraph {
namespace concept {

///
///
///
template <>
double cost( const FeaturePtr & properties)
{
    int indexCost = properties->GetDefnRef()->GetFieldIndex("cost");
    if ( indexCost < 0 ){
        OGRGeometry * g = properties->GetGeometryRef();
        if ( g != NULL ){
            OGRLineString * ls = dynamic_cast<OGRLineString*>(g);
            if ( ls != NULL ){
                return ls->get_Length();
            }
        }
    }else{
        return properties->GetFieldAsDouble("cost");
    }
}


} // namespace concept
} // namespace egraph
