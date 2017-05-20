//
//  DelaunayTriangulation.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef DelaunayTriangulation_hpp
#define DelaunayTriangulation_hpp

#include "DCEL.hpp"
#include "Triangulation.hpp"
#include "ConvexHull.hpp"
#include "primitives.hpp"
#include <cmath>
class DelaunayTriangulation : Triangulation
{
private:
    bool checkConvexity(vector<Vertex> a,vector<Vertex> b);
    bool checkSemicircle(vector<Vertex> a,vector<Vertex> b);
    Edge getEdgeToFlip(DCEL &X);
public:
    Point getCircumcenter(vector<Vertex> a);
    void performLawson(DCEL &X);
    Edge getEncroachedSegment(DCEL &x);
    vector<Vertex> filterTriangle(vector<Vertex> x);
    Face getSkinnyTriangle(DCEL &X,double alpha);
    void Delaunayrefine(DCEL &X,double alpha=0.175);
};

#endif /* DelaunayTriangulation_hpp */
