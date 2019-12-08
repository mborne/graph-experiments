#pragma once

#include <egraph/Point.h>
#include <egraph/LineString.h>

namespace egraph {

    struct Edge {
        /* edge id */
        int id ;
        /* source id */
        int source ;
        /* target id */
        int target ;
        /* direction (-1, 0 or 1)*/
        int direction ;
        /* geometry */
        LineString geom;
    };

}

