#include <egraph/Point.h>

namespace egraph {

///
///
///
std::string asWKT(const Point& g)
{
    std::ostringstream oss;
    oss << "POINT(" << g << ")";
    return oss.str();
}

} // namespace egraph

