#pragma once

#include <egraph/Direction.h>
#include <egraph/Point.h>
#include <egraph/LineString.h>

namespace egraph {

    struct DefaultEdge {
        /* edge id */
        int id ;
        /* source id */
        int source ;
        /* target id */
        int target ;
        /* direction */
        Direction direction ;
        /* geometry */
        LineString geom;
    };

}

