//
//  PointTriangulation.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 25/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef PointTriangulation_hpp
#define PointTriangulation_hpp
#include "primitives.hpp"
#include "Triangulation.hpp"
#include "ConvexHull.hpp"
#include <stdio.h>
class PointTriangulation{
public:
    DCEL *L;
    DCEL *R;
    PointTriangulation();
    
    void triangulate(Data X,bool doDelaunay=false);
};
#endif /* PointTriangulation_hpp */
