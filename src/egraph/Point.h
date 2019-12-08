#pragma once

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Point_2.h>

namespace egraph {
    typedef CGAL::Simple_cartesian<double> Kernel;
    typedef CGAL::Point_2<Kernel> Point ;
}

