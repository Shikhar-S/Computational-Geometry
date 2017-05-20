//
//  PointTriangulation.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 25/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include "PointTriangulation.hpp"
#include "DelaunayTriangulation.hpp"
PointTriangulation::PointTriangulation()
{
    L=R=NULL;
}
void PointTriangulation::triangulate(Data X,bool doDelaunay)
{
    X.orderSweep();
    Point top=X.getPoint(0);
    Point bottom=X.getPoint(X.getSize()-1);
    ConvexHull CH(X);
    Data Y=CH.andrewAlgorithm();
    DCEL __t(Y);
  //  __t.output();
    Data toRemove;
    for(int i=0;i<X.getSize();i++)
    {
        Point p=X.getPoint(i);
        if(p.equals(top))
        {
            continue;
        }
        
        if(p.equals(bottom))
        {
            continue;
        }
        
        if(Y.exists(p))
        {
            toRemove.add(p);
            cout<<"removed\n";
        }
    }
    for(int i=0;i<toRemove.getSize();i++)
        X.remove(toRemove.getPoint(i));
    
    X.orderSweep();
    
    int i=0;
    Data left;
    while(true)
    {
        if(Y.getPoint(i).equals(top))
        {
            break;
        }
        i=(i+1)%Y.getSize();
    }
    while(true)
    {
        left.add(Y.getPoint(i));
        if(Y.getPoint(i).equals(bottom))
        {
            break;
        }
        i=(i+1)%Y.getSize();
    }
    for(int i=X.getSize()-2;i>0;i--)
        left.add(X.getPoint(i));
    L=new DCEL(left);
    //L->output();
    Data right;
    i=0;
    while(true)
    {
        if(Y.getPoint(i).equals(bottom))
        {
            break;
        }
        i=(i+1)%Y.getSize();
    }
    while(true)
    {
        right.add(Y.getPoint(i));
        if(Y.getPoint(i).equals(top))
        {
            break;
        }
        i=(i+1)%Y.getSize();
    }
    for(int i=1;i<X.getSize()-1;i++)
    {
        right.add(X.getPoint(i));
    }
    
    R=new DCEL(right);
    //L->mergeDCEL(R);
   // R->output();

    Triangulation t;
   // t.triangulate(L, L.FaceRecord[0]);
    
   // t.triangulate(R,R.FaceRecord[0]);
    t.performTriangulation(*L);
    cout<<"---Right----\n";
    t.performTriangulation(*R);
    DelaunayTriangulation dt;
    if(doDelaunay)
    {
        dt.performLawson(*L);
        dt.performLawson(*R);
    }
    //L->output();
    //R->output();
    
    
}
