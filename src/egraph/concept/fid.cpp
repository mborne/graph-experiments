#include <egraph/concept/fid.h>

#include <gdal/ogrsf_frmts.h>

namespace egraph {
namespace concept {

///
///
///
template <>
int fid( const FeaturePtr & properties)
{
    return properties->GetFID();
}


} // namespace concept
} // namespace egraph
