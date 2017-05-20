//
//  DelaunayRefinement.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 26/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include "DelaunayRefinement.hpp"
vector<Vertex> DelaunayRefinement::filterTriangle(vector<Vertex> x)
{
    vector<Vertex> ans;
    for(int i=0;i<x.size();i++)
    {
        int prev=(i<1)?(int)x.size()-1:i-1;
        int next=(i+1)%(int)x.size();
        double magPrev=sqrt((x[i].coord.x-x[prev].coord.x)*(x[i].coord.x-x[prev].coord.x)+(x[i].coord.y-x[prev].coord.y)*(x[i].coord.y-x[prev].coord.y));
        double magNext=sqrt((x[i].coord.x-x[next].coord.x)*(x[i].coord.x-x[next].coord.x)+(x[i].coord.y-x[next].coord.y)*(x[i].coord.y-x[next].coord.y));
        double indicator=x[i].coord.crossProduct(x[prev].coord,x[next].coord)/(magNext*magPrev);
        //cout<<indicator<<endl;
        if(indicator>Epsilon || indicator<-Epsilon)
            ans.push_back(x[i]);
    }
    if(ans.size()!=3)
        cout<<"Not returning a triangle\n";
    return ans;
}
pair<bool,DelaunayRefinement::segment> DelaunayRefinement::getEncroachedSegment()
{
    for(vector<segment>::iterator it=S.begin();it!=S.end();it++)
    {
        segment t=*it;
        
        Point start=t.first;
        Point end=t.second;
        Point c;
        c.x=(start.x+end.x)/2;
        c.y=(start.y+end.y)/2;
        
        double r=(c.x-start.x)*(c.x-start.x)+(c.y-start.y)*(c.y-start.y);
        
        for(vector<Point>::iterator it=V.begin();it!=V.end();it++)
        {
            Point tt=*it;
            if(start.equals(tt) || end.equals(tt))
            {
                //cout<<"----------True\n";
                continue;
            }
        
            double r_t=(tt.x-c.x)*(tt.x-c.x)+(tt.y-c.y)*(tt.y-c.y);
            
            if(r>(r_t+Epsilon))
            {
                //cout<<"Encroached by";
                //cout<<it->first<<endl;
                //cout<<"Because of==>"<<t.myaddr<<endl;
                return make_pair(true,t);
                
            }
        }
    }
    Point t_s,t_e;
    segment t(t_s,t_e);
    
    return  make_pair(false,t);
}
Face DelaunayRefinement::getSkinnyTriangle(DCEL *X, double alpha)
{
    for(unordered_map<int, Face>::iterator it=X->FaceRecord.begin();it!=X->FaceRecord.end();it++)
    {
        Face f_temp=it->second;
        if(f_temp.myaddr==1)continue;
        //cout<<it->first<<endl;
        vector<Vertex> v=X->generateFaceVertices(f_temp);
        
        //v=filterTriangle(v);
        for(int i=0;i<3;i++)
        {
            int prev=i<1?2:i-1;
            int next=(i+1)%3;
            double cross=v[i].coord.crossProduct(v[next].coord, v[prev].coord);
            double magPrev=sqrt((v[i].coord.x-v[prev].coord.x)*(v[i].coord.x-v[prev].coord.x)+(v[i].coord.y-v[prev].coord.y)*(v[i].coord.y-v[prev].coord.y));
            double magNext=sqrt((v[i].coord.x-v[next].coord.x)*(v[i].coord.x-v[next].coord.x)+(v[i].coord.y-v[next].coord.y)*(v[i].coord.y-v[next].coord.y));
            double angle=asin(cross/(magNext*magPrev));
            if(angle<alpha+Epsilon)
            {
                cout<<"SIZE OF TRIANGLE------"<<v.size()<<endl;
                cout<<"?????????????????????????????????\n";
                cout<<v[prev].coord.x<<" "<<v[prev].coord.y<<endl;
                cout<<v[i].coord.x<<" "<<v[i].coord.y<<endl;
                cout<<v[next].coord.x<<" "<<v[next].coord.y<<endl;
                
                cout<<"ANGLES==>"<<angle<<" "<<alpha<<endl;
                return f_temp;
            }
            
        }
    }
    Face f;
    return f;
}
void DelaunayRefinement::displayEdges()
{
    cout<<S.size()<<endl;
    for(vector<DelaunayRefinement::segment>::iterator it=S.begin();it!=S.end();it++)
    {
        cout<<it->first.x<<" "<<it->first.y<<endl;
        cout<<it->second.x<<" "<<it->second.y<<endl;
    }
}
bool DelaunayRefinement::splitEdge(segment e,Point p)
{
    V.push_back(p);
    vector<segment>::iterator it=S.begin();
    for(;it!=S.end();it++)
        if((it->first.equals(e.first) && it->second.equals(e.second)) || (it->first.equals(e.second) && it->second.equals(e.first)))
            break;
    S.erase(it);
    segment t(e.first, p);
    S.push_back(t);
    segment T(p, e.second);
    S.push_back(T);
    return (e.first.distance(p)<threshold || e.second.distance(p)<threshold);
    
}
void DelaunayRefinement::addDimensions(int x)
{
    Point a,b,c,d;
    a.x=x;
    a.y=x;
    V.push_back(a); //250 250
    b.x=x;
    b.y=-x;
    V.push_back(b); //250 -250
    c.x=-x;
    c.y=-x;
    V.push_back(c); //-250 -250
    d.x=x;
    d.y=-x;
    V.push_back(d); // 250 -250
    segment ab(a,b);
    S.push_back(ab);
    segment bc(b,c);
    S.push_back(bc);
    segment cd(c,d);
    S.push_back(cd);
    segment da(d,a);
    S.push_back(da);
}
void DelaunayRefinement::Delaunayrefine(DCEL &X,double alpha)
{
    double xmax=std::numeric_limits<double>::min();
     double xmin=std::numeric_limits<double>::max();
     double ymax=std::numeric_limits<double>::min();
     double ymin=std::numeric_limits<double>::max();
     for(unordered_map<int, Vertex>::iterator it=X.VertexRecord.begin();it!=X.VertexRecord.end();it++)
     {
     xmax=max(xmax,it->second.coord.x);
     xmin=min(xmin,it->second.coord.x);
     ymax=max(ymax, it->second.coord.y);
     ymin=min(ymin,it->second.coord.y);
     }
     //double span=max(xmax-xmin,ymax-ymin);
     
    for(unordered_map<int, Vertex>::iterator it=X.VertexRecord.begin();it!=X.VertexRecord.end();it++)
        V.push_back(it->second.coord);
    
    for(unordered_map<int, Edge>::iterator it=X.EdgeRecord.begin();it!=X.EdgeRecord.end();it++)
    {
        bool flag=true;
        for(vector<segment>::iterator itt=S.begin();itt!=S.end();itt++)
        {
            if(it->second.p_start->coord.equals(itt->second) && it->second.p_twin->p_start->coord.equals(itt->first))
                flag=false;
        }
        segment t((it->second.p_start->coord),(it->second.p_twin->p_start->coord));
        if(flag)
            S.push_back(t);

    }
    //addDimensions(250);
    
    PointTriangulation pT;
    DelaunayTriangulation dt;
    bool repeat=true;
    while(repeat)
    {
        Data pointset(V);
        PointTriangulation pt;
        pt.triangulate(pointset,true);//////<error
        repeat=false;
        pair<bool,segment > g=getEncroachedSegment();
        segment e=g.second;
        while(g.first)
        {
            repeat=true;
            
            Point start=e.first;
            Point end=e.second;
            Point p;
            p.x=(start.x+end.x)/2;
            p.y=(start.y+end.y)/2;
            
            if(splitEdge(e,p))
                ;//    break;
            cout<<"AFTER SPLIT\n";
            cout<<e.first.x<<" "<<e.first.y<<" "<<e.second.x<<" "<<e.second.y<<endl;
            cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
            g=getEncroachedSegment();
            e=g.second;
        }
        
        
        
        int from=-1;
        Face f=getSkinnyTriangle(pt.L,alpha);////<eror
        if(f.myaddr==-1)
        {
            f=getSkinnyTriangle(pt.R, alpha);
            from=2;
        }
        else
            from=1;
           
        //vcout<<f.myaddr<<endl;
        if(f.myaddr!=-1)
        {
            repeat = true;
            vector<Vertex> lop;
            
            if(from==1)
                lop=(pt.L->generateFaceVertices(f));
            else
                lop=(pt.R->generateFaceVertices(f));
            
            Point circumcenter=dt.getCircumcenter(lop);
            
            vector<segment> encroachedUpon;
            for(vector<segment>::iterator it=S.begin();it!=S.end();it++)
            {
                segment t=*it;
                Point start=t.first;
                Point end=t.second;
                Point c;
                c.x=(start.x+end.x)/2;
                c.y=(start.y+end.y)/2;
                double r=(c.x-start.x)*(c.x-start.x)+(c.y-start.y)*(c.y-start.y);
                double r_t=(circumcenter.x-c.x)*(circumcenter.x-c.x)+(circumcenter.y-c.y)*(circumcenter.y-c.y);
                if(r>(r_t+Epsilon))
                    encroachedUpon.push_back(t);
            }
            int v=(int)encroachedUpon.size();
            while(encroachedUpon.size()!=0)
            {
                segment e=*encroachedUpon.begin();
                Point start=e.first;
                Point end=e.second;
                Point p;
                p.x=(start.x+end.x)/2;
                p.y=(start.y+end.y)/2;
                splitEdge(e,p);
                cout<<"Split second Phase\n";
                vector<segment>::iterator it=encroachedUpon.begin();
                for(;it!=encroachedUpon.end();it++)
    if((it->first.equals(e.first) && it->second.equals(e.second)) || (it->first.equals(e.second) && it->second.equals(e.first)))
                        break;
                encroachedUpon.erase(it);
            }
            if(v==0)
            {
                if(circumcenter.x<-250 || circumcenter.x>250 || circumcenter.y<-250 || circumcenter.y>250)
                {
                    cout<<"Should Terminate\n";
                    //repeat=false;
                   // break;
                }
                cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
                cout<<"DONE\n";
                cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
                V.push_back(circumcenter);
            }
           
            
        }
         cout<<"Completed an iteration--->"<<V.size()<<" ,,,"<<S.size()<<endl;
    }
    Data vertices(V);
    pT.triangulate(vertices,true);
    pT.L->output();
    pT.R->output();
    displayEdges();
}
