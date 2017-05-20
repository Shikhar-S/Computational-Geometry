//
//  Triangulation.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include "Triangulation.hpp"
int Triangulation::typeOfVertex(Vertex v,DCEL &X)
{
    int n_idx=(v.myaddr+1)%(int)X.VertexRecord.size();
    int p_idx=(v.myaddr==0)?(int)X.VertexRecord.size()-1:v.myaddr-1;
    Vertex next=(X.VertexRecord[n_idx]); //obtain from index i-1 and i+1
    Vertex prev=(X.VertexRecord[p_idx]);
    if(v<next && v<prev)
    {
        if(v.coord.crossProduct(prev.coord,next.coord)>0)
        {
            return mergeVertex;
        }
        else
        {
            return endVertex;
        }
    }
    if(next<v && prev<v)
    {
        if(v.coord.crossProduct(prev.coord,next.coord)>0)
        {
            return splitVertex;
        }
        else
        {
            return startVertex;
        }
    }
    return regularVertex;
}
void Triangulation::HandleStartVertex(Vertex v,DCEL &X)
{
    Tau.insert((X.EdgeRecord[v.myaddr]),v); //ei=vi to vi+1
    Tau.setHelper(X.EdgeRecord[v.myaddr],v);
}
void Triangulation::HandleEndVertex(Vertex v,DCEL &X)
{
    int idx=(v.myaddr==0)?((int)X.VertexRecord.size()-1):(v.myaddr-1);
    if(typeOfVertex(Tau.helper[idx],X)==mergeVertex)
    {
        X.addEdge(Tau.helper[idx],v);
    }
    
    
    
    Tau.remove(X.EdgeRecord[idx]);
}
void Triangulation::HandleSplitVertex(Vertex v,DCEL &X)
{
    
    Edge e_left=Tau.find(v);
    X.addEdge(v,Tau.helper[e_left.myaddr]);
    Tau.helper[e_left.myaddr]=v;
    Tau.insert(X.EdgeRecord[v.myaddr],v);
    Tau.setHelper(X.EdgeRecord[v.myaddr],v);
}
void Triangulation::HandleMergeVertex(Vertex v,DCEL &X)
{
    // cout<<"HELPER EDGE IS ---";
    //cout<<e_left.myaddr<<endl;
    
    int idx=(v.myaddr==0)?((int)X.VertexRecord.size()-1):(v.myaddr-1);
    
    Vertex help=Tau.helper[idx];
    //cout<<help.myaddr<<"&&&&&&&&&&&&&&&&&"<<endl;
    if(typeOfVertex(help,X)==mergeVertex)
    {
        X.addEdge(help,v);
    }
    Tau.remove(X.EdgeRecord[idx]);
    Edge e_left=Tau.find(v);
    cout<<"HELPER EDGE IS ---";
    cout<<e_left.myaddr<<endl;
    if(typeOfVertex(Tau.helper[e_left.myaddr],X)==mergeVertex)
    {
        X.addEdge(v,Tau.helper[e_left.myaddr]);
    }
    Tau.setHelper(e_left,v);
}

bool Triangulation::check_polyIsToRight(Vertex v,Face f,DCEL &X)
{
    Edge e=*(f.p_incident);
    
    while(*(e.p_start)!=v)
    {
        e=*(e.p_next);
        // cout<<e.myaddr<<",,,,,,,";
    }
    e=*(e.p_next);
    
    Vertex n=*(e.p_start);
    
    if(n<v)
        return true;
    return false;
}
void Triangulation::HandleRegularVertex(Vertex v,DCEL &X)
{
    //cout<<"iS IT??"<<endl;
    int idx=(v.myaddr==0)?((int)X.VertexRecord.size()-1):(v.myaddr-1);
    //cout<<(X.EdgeRecord[v.myaddr].p_incident)->myaddr<<endl;
    //cout<<(X.EdgeRecord[13].p_incident)->myaddr<<endl;
    if(check_polyIsToRight(v,*(X.EdgeRecord[v.myaddr].p_incident),X))//*********** CHECK FOR FACE THING **********//check for the polygon to lie on right side of vertex v
    {
        cout<<"WRONG"<<endl;
        if(typeOfVertex(Tau.helper[idx],X)==mergeVertex)
        {
            X.addEdge(Tau.helper[idx],v);
        }
        Tau.remove(X.EdgeRecord[idx]);
        Tau.insert(X.EdgeRecord[(idx+1)%X.VertexRecord.size()],v);
        Tau.setHelper(X.EdgeRecord[(idx+1)%X.VertexRecord.size()],v);
    }
    else
    {
        Edge e_left=Tau.find(v);
        cout<<"Reg Vertex's left edge is"<<e_left.myaddr<<endl;
        if(typeOfVertex(Tau.helper[e_left.myaddr],X)==mergeVertex)
        {
            X.addEdge(v,Tau.helper[e_left.myaddr]);
        }
        Tau.setHelper(e_left,v);
    }
}
void Triangulation::makeMonotone(DCEL &X)
{
    priority_queue<Vertex> Q;
    for(unordered_map<int,Vertex>::iterator it=X.VertexRecord.begin();it!=X.VertexRecord.end();it++)
    {
        Q.push(it->second);
    }
    
    while(!Q.empty())
    {
        Vertex t=Q.top();
        cout<<"Currently on vertex ---> "<<t.myaddr<<endl;
        Q.pop();
        int typ=typeOfVertex(t,X);
        switch(typ)
        {
            case mergeVertex: HandleMergeVertex(t,X);break;
            case splitVertex: HandleSplitVertex(t,X);break;
            case regularVertex: HandleRegularVertex(t,X);break;
            case startVertex: HandleStartVertex(t,X);break;
            case endVertex: HandleEndVertex(t,X);break;
        }
    }
    
    
}
bool Triangulation::leftChain(Vertex v,unordered_map<int,string> &chain) //CHANGE WHEREVER CALLED!!!!!!!!!!!!!!!!
{
    return chain[v.myaddr]=="left";
}
bool Triangulation::rightChain(Vertex v,unordered_map<int,string> &chain)   //CHANGE WHEREVER CALLED!!!!!!!!!!!!!!!!
{
    return chain[v.myaddr]=="right";
}
bool Triangulation::inside(Vertex a,Vertex b,Vertex c,unordered_map<int, string> &chain)
{
    return (b.coord.crossProduct(a.coord,c.coord)>0 && rightChain(b,chain)) || (leftChain(b,chain) && b.coord.crossProduct(a.coord,c.coord)<0);
}
bool Triangulation::diffchains(Vertex a,Vertex b,unordered_map<int,string> &chain)
{
    //returns true if a and b are on different chains
    return (leftChain(a,chain) && rightChain(b,chain)) || (rightChain(a,chain) && leftChain(b,chain));
}
void Triangulation::triangulate(DCEL &X,Face &f)
{
    stack<Vertex> S;
    unordered_map<int,string> chain;
    //cout<<"this is face number"<<f.myaddr<<"  incident on edge starting from "<<f.p_incident->p_start->myaddr<<endl;
    //merge left and right chains to get result in a vector.
    vector<Edge> surrounding_edges=X.walkAround(f);
    vector<Vertex> surrounding_vertices;
    for(vector<Edge>::iterator it=surrounding_edges.begin();it!=surrounding_edges.end();it++)
        surrounding_vertices.push_back(*(it->p_start));
    
    Vertex start;
    start = *(surrounding_vertices.begin());
    
    for(vector<Vertex>::iterator it=surrounding_vertices.begin();it!=surrounding_vertices.end();it++)
    {
        
        if(start<*it)
            start=*it;
    }
    Vertex left,right;
    Edge left_e,right_e;
    
    for(vector<Edge>::iterator it=surrounding_edges.begin();it!=surrounding_edges.end();it++)
    {
        if(*(it->p_start)==start)
        {
            left=*(it->p_twin->p_start);
            left_e=*it;
        }
        if(*(it->p_twin->p_start)==start)
        {
            right=*(it->p_start);
            right_e=*it;
        }
    }
    vector<Vertex> v;
    v.push_back(start);
    while(true)
    {
        if(right<left)
        {
            if(chain.size()==0)
                chain[start.myaddr]=("left");
            chain[left.myaddr]=("left");
            v.push_back(left);
            left_e=*(left_e.p_next);
            left=*(left_e.p_twin->p_start);
        }
        else if(left<right)
        {
            if(chain.size()==0)
                chain[start.myaddr]=("right");
            chain[right.myaddr]=("right");
            v.push_back(right);
            right_e=*(right_e.p_prev);
            right=*(right_e.p_start);
        }
        if(left==right) //bottom
        {
            v.push_back(left);
            break;
        }
    }
    //cout<<"!%#%@!$#%#^%$&$%&%^*!#\n";
  //  for(vector<Vertex>::iterator it=v.begin();it!=v.end();it++)
    //{
      //  cout<<it->myaddr<<endl;
   // }
   // cout<<"Linear time chain formed\n";
    S.push(v[0]);
    S.push(v[1]);
    for(int i=2;i<v.size()-1;i++)
    {
        if(diffchains(S.top(),v[i],chain))
        {
            while(!S.empty())
            {
                Vertex u=S.top();
                S.pop();
                if(!S.empty())
                {
                    X.addEdge(u,v[i]);
                }
            }
            S.push(v[i-1]);
            S.push(v[i]);
        }
        else
        {
            
            Vertex prev=S.top();
            S.pop();
            while(!S.empty() && inside(prev,v[i],S.top(),chain))
            {
                X.addEdge(v[i],S.top());
                prev=S.top();
                S.pop();
            }
            S.push(prev);
            S.push(v[i]);
        }
        stack<Vertex> st;
        //cout<<"Status of stack\n";
        while(!S.empty())
        {
            Vertex kk=S.top();
            S.pop();
            st.push(kk);
           // cout<<kk.myaddr<<"::::";
        }
        //cout<<endl;
        while(!st.empty())
        {
            S.push(st.top());
            st.pop();
        }
    }
    
    S.pop();
    while(S.size()>1)
    {
        
        X.addEdge(v[v.size()-1],S.top());
        S.pop();
    }
}
void Triangulation::performTriangulation(DCEL &X)
{
    
    makeMonotone(X);
    //X.display();
    //X_i stores each monotone polygon everytime.
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    for(unordered_map<int,Face>::iterator it=X.FaceRecord.begin();it!=X.FaceRecord.end();it++)
    {
        if(it->first!=1)
             triangulate(X,it->second);
    }
    //generate a clockwise list of vertices and construct X before sending... <-do this in a loop
    
}
