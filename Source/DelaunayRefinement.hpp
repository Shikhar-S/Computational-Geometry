//
//  DelaunayRefinement.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 26/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef DelaunayRefinement_hpp
#define DelaunayRefinement_hpp
#include "Triangulation.hpp"
#include "DelaunayTriangulation.hpp"
#include "PointTriangulation.hpp"
#include "DCEL.hpp"
#include "ConvexHull.hpp"
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#define threshold 1e-3
class DelaunayRefinement
{
public:
    struct segment{
        Point first;
        Point second;
        segment(Point a,Point b): first(a), second(b)
        {
            
        }
    };
    
    vector<Point> V;
    vector<segment> S;
    //set<pair<Point,Point> ,bool(*)(const Point&, const Point&) > S(&comp);
    
    
public:
    void displayEdges();
    void addDimensions(int x);
    bool splitEdge(segment e,Point p);
    pair<bool, segment > getEncroachedSegment();
    vector<Vertex> filterTriangle(vector<Vertex> x);
    Face getSkinnyTriangle(DCEL *X,double alpha);
    void Delaunayrefine(DCEL &X,double alpha=0.175);
};
#endif /* DelaunayRefinement_hpp */
