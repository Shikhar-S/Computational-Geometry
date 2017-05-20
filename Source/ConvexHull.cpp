//
//  ConvexHull.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include "ConvexHull.hpp"
ConvexHull::ConvexHull(Data obj)
{
    inp=obj;
    
}
Data ConvexHull::getInput()
/**
 *Accessor for Ouput
 */
{
    return inp;
}

Data ConvexHull::grahamScan()
/**
 *Performs Graham Scan on the given input data object
 */
{
    Data outp;
    outp.setSize(0);
    int N=inp.getSize();
    if(N<3)return outp;
    /*
     get the anchor
     */
    outp.setSize(0);
    Point min_p=inp.getPoint(0);
    int min_idx=0;
    for (int i=0; i<N; i++) {
        Point current=inp.getPoint(i);
        if (current.y<min_p.y || (current.y==min_p.y && current.x<min_p.x)) {
            min_p=current;
            min_idx=i;
        }
    }
    outp.add(min_p);
    inp.swap(0,min_idx);
    inp.setOrigin(min_p);
    /*sort points radially based on anchor*/
    inp.orderRadially();
    outp.add(inp.getPoint(1));
    outp.add(inp.getPoint(2));
    int K=outp.getSize();
    for (int i=3; i<N; i++) {
        // remove elements until we get a left turn
        while(K>=2 && outp.getPoint(K-2).crossProduct(outp.getPoint(K-1),inp.getPoint(i))<=0)
        {
            K--;
            outp.setSize(K);
        }
        outp.add(inp.getPoint(i));
        K=outp.getSize();
    }
    return outp;
}
Data ConvexHull::jarvisMarch()
/**
 *Computes Convex Hull via Jarvis March algorithm Complexity: O(NH)
 *where H := number of points on Hull.
 */
{
    Data outp;
    int N=inp.getSize();
    if(N<3)return outp;
    //get the leftmost point
    outp.setSize(0);
    Point min_p=inp.getPoint(0);
    int min_idx=0;
    for (int i=0; i<N; i++) {
        Point current=inp.getPoint(i);
        if (current.x<min_p.x || (current.x==min_p.x && current.y<min_p.y)) {
            min_p=current;
            min_idx=i;
        }
    }
    
    inp.swap(0,min_idx);
    
    int current_idx=0;
    int next_idx;
    do{
        outp.add(inp.getPoint(current_idx));
        next_idx=(current_idx+1)<N?current_idx+1:0;
        //get the point which is rightmost from current point
        for(int i=0;i<N;i++){
            Point anchor=inp.getPoint(current_idx);
            if(anchor.crossProduct(inp.getPoint(i),inp.getPoint(next_idx))>0)
            {
                next_idx=i;
            }
            
        }
        current_idx=next_idx;
    }while(current_idx!=0);// continue till we come back to starting point
    return outp;
    
}
Data ConvexHull::andrewAlgorithm()
/**
 *Computes Convex Hull via Andrew algorithm Complexity: O(Nlog N)
 */
{
    Data outp;
    int N=inp.getSize();
    if(N<3)return outp;
    // order elements lexicographically
    inp.orderLexicographically();
    
    //compute hull in two parts upper and lower
    int K=0;
    outp.setSize(K);
    for(int i=0;i<N;i++)
    {
        //include an element only if it is a left turn
        while(K>=2 && outp.getPoint(K-2).crossProduct(outp.getPoint(K-1),inp.getPoint(i))<0-Epsilon)
        {
            K--;
            outp.setSize(K);
        }
        outp.add(inp.getPoint(i));
        K=outp.getSize();
    }
    for(int i=N-2,temp=K+1;i>=0;i--)
    {
        while(K>=temp && outp.getPoint(K-2).crossProduct(outp.getPoint(K-1),inp.getPoint(i))<0-Epsilon)
        {
            K--;
            outp.setSize(K);
        }
        outp.add(inp.getPoint(i));
        K=outp.getSize();
    }
    K--;// to remove extra duplicate element because first=last
    outp.setSize(K);
    return outp;
}
void ConvexHull::display()
/**
 *displays input and output list of points
 */
{
    cout<<"INPUT SET"<<endl;
    inp.display();
    cout<<"OUTPUT SET"<<endl;
    andrewAlgorithm().display();
}
