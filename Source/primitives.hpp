//
//  primitives.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 18/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef primitives_hpp
#define primitives_hpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define Epsilon 1e-9
double MOD(double x);
/**
 *Implementation of absolute function for real floating point values
 */

struct Point{
    /**
     *Stores Points as (x,y) tuple and provides function for determining orientation
     *via cross product.
     */
    double x;///< x coordinate
    double y;///< y coordinate
    bool equals(const Point &t)const;
    /**
     *Checks for equality between two points
     */
    double crossProduct(const Point &A,const Point &B);
    /**
     *return cross product direction between OA and OB where O := calling Point
     *right turn if > 0
     *left turn if < 0
     *collinear points if = 0
     */
    double distance(const Point &A);
   // bool operator< (const Point &B)const;
    
   
    
};
#endif /* primitives_hpp */
