#pragma once

#include <vector>
#include <egraph/Point.h>

namespace egraph {
    typedef std::vector<Point> LineString ;

    std::string asWKT(const LineString& g);
}

