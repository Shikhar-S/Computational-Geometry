#ifndef BST_hpp
#define BST_hpp

#include "Vertex.hpp"
#include "Edge.hpp"
#include <set>
#include <utility>
#include <unordered_map>
struct node
{
    int key;
    Edge e;
    node *parent;
    char color;
    node *left;
    node *right;
    int height;
};
class RBtree
{
    node *root;
    node *q;
    public :
    double compareAt;
        RBtree()
    {
        q=NULL;
        root=NULL;
    }
    void insert(Edge);
    void insertfix(node *);
    void leftrotate(node *);
    void rightrotate(node *);
    void del(Edge);
    void delfix(node *);
    void disp();
    void display( node *);
    void search(Edge);
    double getPriority(const Edge&);
    node* pred(node *);
    node* successor(node *);
    node* least();
    node* get(Edge e);
};


class AVLtree
{
    
public:
    
    node *root;
    double compareAt;
    AVLtree()
    {
        root=NULL;
    }
    int height(node *);
    node* newNode(Edge e);
    node* rightRotate(node *);
    node* leftRotate(node *);
    int getBalance(node *);
    node *insert(node *,Edge);
    double getPriority(const Edge&);
    node* pred(Edge);
    node* minValueNode(node *);
    node *deleteNode(node *,Edge);
};




class BST
{
public:
    struct edge_compare {
        double compareAt;
        double getPriority(const Edge &	e)
        {
            Vertex start=*(e.p_start);
            Vertex end=*(e.p_twin->p_start);
            if(end.coord.y==start.coord.y)
                return start.coord.x;
            double r=(end.coord.y-start.coord.y);
            //cout<<e.myaddr<<"PRiority---> "<<r<<endl;
            
            return (((compareAt-start.coord.y)*(end.coord.x-start.coord.x))/r)+start.coord.x;
            
        }
        bool operator() (const Edge &first, const Edge &other) {
            return getPriority(first)<getPriority(other);
        }
    } comp;
    AVLtree S;
    //set<Edge, edge_compare> S;
    std::unordered_map<int,Vertex> helper;
    
public:
    void insert(Edge e,Vertex v);
    void setHelper(Edge e,Vertex v);
    void remove(Edge e);
    Edge find(Vertex v);
};
#endif //BST_hpp
