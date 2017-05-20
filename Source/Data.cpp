//
//  Data.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 18/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include "Data.hpp"
#include <functional>
void Data::orderSweep()
{
        sort(points.begin(),points.end(),comp_ysweep);
}
bool Data::exists(Point p)
{
    for(int i=0;i<points.size();i++)
        if(points[i].equals(p))
            return true;
    return false;
}
Data::Data(){
        N=0;
    }
    Data::Data(Point arg_points[],int sz)
    {
        N=sz;
        for(int i=0;i<N;i++)
            points.push_back(arg_points[i]);
    }
Data::Data(vector<Point> p)
{
    points=p;
    N=(int)p.size();
}
    void Data::getInput()
    {
        cin>>N;
        for(int i=0;i<N;i++)
        {
            double x,y;
            cin>>x>>y;
            Point t={x,y};
            points.push_back(t);
        }
        points.resize(N);
    }
    void Data::add(Point x)
    {
        if(N<points.size())
        {
            points[N++]=x;
        }
        else
        {
            points.push_back(x);
            N++;
        }
        
    }
    bool Data::remove(Point x)
        {
        bool flag=false;
        int i;
        for(i=0;i<N;i++)
        {
            if(x.equals(points[i]))
            {
                flag=true;
                break;
            }
            
        }
        for(i=i+1;i<N;i++)
        {
            points[i-1]=points[i];
        }
        if(flag)
            N--;
        points.resize(N);
        return flag;
    }
bool Data::comp_graham(const Point &a,const Point &b)
/**
 *To order points according to radial angle from "anchor_Graham"
 */
{
    double x=origin.crossProduct(a,b);
    return x>0;
}
void Data::orderRadially()
/**
 *sorts list radially assuming first element as anchor
 */
{
    vector<Point>::iterator it=points.begin();
    it++;
    sort(it,points.end(),std::bind(&Data::comp_graham,this,std::placeholders::_1,std::placeholders::_2));
}
    void Data::orderLexicographically()
    
    {
        sort(points.begin(),points.end(),comp_andrew);
    }
    
    Point Data::getPoint(int idx)
    {
        return points.at(idx);
    }
    void Data::setPoint(int idx,Point value)
        {
        points[idx]=value;
    }
    int Data::getSize()
    {
        return N;
    }
    void Data::setSize(int x)
    {
        N=x;
        points.resize(N);
    }
    void Data::setOrigin(Point x)
    {
        origin=x;
    }
    void Data::display()
    
    {
        cout<<N<<endl;
        for (int i=0; i<N;i++) {
            cout<<points[i].x<<" "<<points[i].y<<"\n";
        }
        cout<<endl;
    }
    void Data::swap(int a,int b)
    
    {
        Point t=points[a];
        points[a]=points[b];
        points[b]=t;
    }
    
