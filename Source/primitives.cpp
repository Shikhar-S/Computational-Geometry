//
//  primitives.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 18/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//
#include "primitives.hpp"
using namespace std;
double MOD(double x)
{
    return x<0?-x:x;
}
bool Point::equals(const Point &t)const
{
    return (MOD(x-t.x)<Epsilon && MOD(y-t.y)<Epsilon);
}
double Point::crossProduct(const Point &A,const Point &B)
{
    return (A.x-x)*(B.y-y)-(A.y-y)*(B.x-x);
}
double Point::distance(const Point &A)
{
    return sqrt((x-A.x)*(x-A.x)+(y-A.y)*(y-A.y));
}
/*bool Point::operator< (const Point &B)const
{
    return ((x<B.x) || (x==B.x && y<B.y));
}*/
