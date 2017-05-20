//
//  main.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 18/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//
//////////////////////////////test case generation script, result visualization script//////////////////////
#include "DCEL.hpp"
#include "primitives.hpp"
#include "Vertex.hpp"
#include "Face.hpp"
#include "Edge.hpp"
#include "Data.hpp"
#include "Triangulation.hpp"
#include "ConvexHull.hpp"
#include "DelaunayTriangulation.hpp"
#include "PointTriangulation.hpp"
#include "DelaunayRefinement.hpp"
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    Data x;
    x.getInput();
    /////////////////////////////////CONVEX - HULL ---pgen,chvis///////////////////////////////////////
    /*
    ConvexHull CH(x);
    Data outp=CH.jarvisMarch();
    DCEL X(outp);
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    X.output();
    x.display();*/
    
    
    ///////////////////////////////////TRIANGULATION----gen,vis/////////////////////////////////////
    
    /*DCEL Y(x);
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    
    Y.display();
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    
    Triangulation t;
    t.performTriangulation(Y);
    Y.output();
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    */
    ///////////////////////////////DELAUNAY TRIANGULATION--gen,vis//////////////////////////
    /*
     DelaunayTriangulation dt;
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    DCEL Y(x);
    Triangulation t;
    t.performTriangulation(Y);
    Y.output();
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    dt.performLawson(Y);
    Y.output();
    */
    /////////////////////////////POINT SET TRIANGULATION----pgen,pvis//////////////////////////////////////////
    /*
    DCEL Y(x);
    Y.output();
    PointTriangulation pt;
    pt.triangulate(x);
    pt.L->output();
    pt.R->output();
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    */
    /////////////////////////////PROJECT--TO-FIX////////////////////////////////////////
    /*
    DelaunayRefinement dR;
    DCEL X(x);
    dR.Delaunayrefine(X);
    */
    ///////////////////////////////////////////////////////////////////////////
    
}
