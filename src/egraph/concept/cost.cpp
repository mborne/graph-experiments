#include <egraph/concept/cost.h>

#include <ogrsf_frmts.h>

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
        return 1.0;
    }else{
        return properties->GetFieldAsDouble(indexCost);
    }
}


} // namespace concept
} // namespace egraph
