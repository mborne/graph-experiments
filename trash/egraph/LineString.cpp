#include <egraph/LineString.h>

namespace egraph {

///
///
///
std::string asWKT(const LineString& g)
{
    std::ostringstream oss;
    oss << "LINESTRING";
    if ( g.empty() ){
        oss << " EMPTY";
    }else{
        oss << "(";
        bool first = true;
        for ( const Point & p : g ){
            if ( ! first ){
                oss << ", ";
            }else{
                first = false;
            }
            oss << p ;
        }
        oss << ")";
    }
    return oss.str();
}

} // namespace egraph

