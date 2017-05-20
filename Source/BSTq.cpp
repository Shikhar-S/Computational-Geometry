#ifndef BST_H
#define BST_H
#include "Vertex.h"
#include "Edge.h"
#include <set>
#include <utility>
struct node
{
    int key;
    Edge e;
    node *parent;
    char color;
    node *left;
    node *right;
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
node *get(Edge e)
{
    Node *r=root;
        while(r!=NULL)
        {
            if(getPriority(r->e)<getPriority(e))
                r=r->right;
            else if(getPriority(r->e)>getPriority(e))
                r=r->left;
            else
                break;
        }
    return r;
}
node *least()
{
    node *r=root;
    while(r->left!=NULL)
          r=r->left;
    return r;
}
double RBtree::getPriority(const Edge & e)
{
    Vertex start=*(e.p_start);
    Vertex end=*(e.p_twin->p_start);
    if(end.coord.y==start.coord.y)
        return start.coord.x;
    double r=(end.coord.y-start.coord.y);
    //cout<<e.myaddr<<"PRiority---> "<<r<<endl;

    return (((compareAt-start.coord.y)*(end.coord.x-start.coord.x))/r)+start.coord.x;

}

void RBtree::insert(Edge ei)
{
    int z,i=0;
    //cout<<"\nEnter key of the node to be inserted: ";
    //cin>>z;
    node *p,*q;
    node *t=new node;
    //t->key=z;
    t->e=ei;
    t->left=NULL;
    t->right=NULL;
    t->color='r';
    p=root;
    q=NULL;
    if(root==NULL)
    {
        root=t;
        t->parent=NULL;
    }
    else
    {
        while(p!=NULL)
        {
            q=p;
            if(getPriority(p->e)<getPriority(t->e))
                p=p->right;
            else
                p=p->left;
        }
        t->parent=q;
        if(getPriority(q->e)<getPriority(t->e))
            q->right=t;
        else
            q->left=t;
    }
    insertfix(t);
}
void RBtree::insertfix(node *t)
{
    node *u;
    if(root==t)
    {
        t->color='b';
        return;
    }
    while(t->parent!=NULL&&t->parent->color=='r')
    {
        node *g=t->parent->parent;
        if(g->left==t->parent)
        {
            if(g->right!=NULL)
            {
                u=g->right;
                if(u->color=='r')
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if(t->parent->right==t)
                {
                    t=t->parent;
                    leftrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                rightrotate(g);
            }
        }
        else
        {
            if(g->left!=NULL)
            {
                u=g->left;
                if(u->color=='r')
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if(t->parent->left==t)
                {
                    t=t->parent;
                    rightrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                leftrotate(g);
            }
        }
        root->color='b';
    }
}

node* RBtree::successor(node *p)
{
      node *y=NULL;
     if(p->left!=NULL)
     {
         y=p->left;
         while(y->right!=NULL)
              y=y->right;
     }
     else
     {
         y=p->right;
         while(y->left!=NULL)
              y=y->left;
     }
     return y;
}

void RBtree::del(Edge ei)
{
    if(root==NULL)
    {
        cout<<"\nEmpty Tree." ;
        return ;
    }
    int x;
    //cout<<"\nEnter the key of the node to be deleted: ";
    //cin>>x;
    node *p;
    p=root;
    node *y=NULL;
    node *q=NULL;
    int found=0;
    while(p!=NULL&&found==0)
    {
        if(p->e==ei)
            found=1;
        if(found==0)
        {
            if(getPriority(p->e)<getPriority(ei))
                p=p->right;
            else
                p=p->left;
        }
    }
    if(found==0)
    {
        cout<<"\nElement Not Found.";
        return ;
    }
    else
    {

        if(p->left==NULL||p->right==NULL)
            y=p;
        else
            y=successor(p);

        if(y->left!=NULL)
            q=y->left;
        else
        {
            if(y->right!=NULL)
                q=y->right;
            else
                q=NULL;
        }
        if(q!=NULL)
            q->parent=y->parent;
        if(y->parent==NULL)
            root=q;
        else
        {
            if(y==y->parent->left)
                y->parent->left=q;
            else
                y->parent->right=q;
        }
        if(y!=p)
        {
            p->color=y->color;
            p->key=y->key;
        }
        if(y->color=='b')
            delfix(q);
    }
}

void RBtree::delfix(node *p)
{
    node *s;
    while(p!=root&&p->color=='b')
    {
        if(p->parent->left==p)
        {
            s=p->parent->right;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                leftrotate(p->parent);
                s=p->parent->right;
            }
            if(s->right->color=='b'&&s->left->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->right->color=='b')
                {
                    s->left->color=='b';
                    s->color='r';
                    rightrotate(s);
                    s=p->parent->right;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->right->color='b';
                leftrotate(p->parent);
                p=root;
            }
        }
        else
        {
            s=p->parent->left;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                rightrotate(p->parent);
                s=p->parent->left;
            }
            if(s->left->color=='b'&&s->right->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->left->color=='b')
                {
                    s->right->color='b';
                    s->color='r';
                    leftrotate(s);
                    s=p->parent->left;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->left->color='b';
                rightrotate(p->parent);
                p=root;
            }
        }
        p->color='b';
        root->color='b';
    }
}

void RBtree::leftrotate(node *p)
{
    if(p->right==NULL)
        return ;
    else
    {
        node *y=p->right;
        if(y->left!=NULL)
        {
            p->right=y->left;
            y->left->parent=p;
        }
        else
            p->right=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->left=p;
        p->parent=y;
    }
}
void RBtree::rightrotate(node *p)
{
    if(p->left==NULL)
        return ;
    else
    {
        node *y=p->left;
        if(y->right!=NULL)
        {
            p->left=y->right;
            y->right->parent=p;
        }
        else
            p->left=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->right=p;
        p->parent=y;
    }
}

node* RBtree::pred(node *p)
{
    node *y=NULL;
    if(p->left!=NULL)
    {
        y=p->left;
        while(y->right!=NULL)
            y=y->right;
    }
    else
    {
        y=p;
        bool flag=0;
        while(y->parent!=NULL)
        {
            node *k=y->parent;
            if(k->right==y)
            {
                y=k;
                flag=1;
                break;
            }
            else
            {
                y=k;
            }
        }
        if(flag==0)
            y=NULL;
    }
    return y;
}

void RBtree::disp()
{
    display(root);
}
void RBtree::display(node *p)
{
    if(root==NULL)
    {
        cout<<"\nEmpty Tree.";
        return ;
    }
    if(p!=NULL)
    {
        cout<<"\n\t NODE: ";
        cout<<"\n Key: "<<p->key;
        cout<<"\n Colour: ";
        if(p->color=='b')
            cout<<"Black";
        else
            cout<<"Red";
        if(p->parent!=NULL)
            cout<<"\n Parent: "<<p->parent->key;
        else
            cout<<"\n There is no parent of the node.  ";
        if(p->right!=NULL)
            cout<<"\n Right Child: "<<p->right->key;
        else
            cout<<"\n There is no right child of the node.  ";
        if(p->left!=NULL)
            cout<<"\n Left Child: "<<p->left->key;
        else
            cout<<"\n There is no left child of the node.  ";
        cout<<endl;
        if(p->left)
        {
            cout<<"\n\nLeft:\n";
            display(p->left);
        }
        /*else
         cout<<"\nNo Left Child.\n";*/
        if(p->right)
        {
            cout<<"\n\nRight:\n";
            display(p->right);
        }
        /*else
         cout<<"\nNo Right Child.\n"*/
    }
}
void RBtree::search(Edge ei)
{
    if(root==NULL)
    {
        cout<<"\nEmpty Tree\n" ;
        return  ;
    }
    int x;
    //cout<<"\n Enter key of the node to be searched: ";
    //cin>>x;
    node *p=root;
    int found=0;
    while(p!=NULL&& found==0)
    {
        if(p->e==ei)
            found=1;
        if(found==0)
        {
            if(getPriority(p->e)<getPriority(ei))
                p=p->right;
            else
                p=p->left;
        }
    }
    if(found==0)
        cout<<"\nElement Not Found.";
    else
    {
        cout<<"\n\t FOUND NODE: ";
        cout<<"\n Key: "<<p->key;
        cout<<"\n Colour: ";
        if(p->color=='b')
            cout<<"Black";
        else
            cout<<"Red";
        if(p->parent!=NULL)
            cout<<"\n Parent: "<<p->parent->key;
        else
            cout<<"\n There is no parent of the node.  ";
        if(p->right!=NULL)
            cout<<"\n Right Child: "<<p->right->key;
        else
            cout<<"\n There is no right child of the node.  ";
        if(p->left!=NULL)
            cout<<"\n Left Child: "<<p->left->key;
        else
            cout<<"\n There is no left child of the node.  ";
        cout<<endl;

    }
}
/*
 int main()
 {
 int ch,y=0;
 RBtree obj;
 do
 {
 cout<<"\n\t RED BLACK TREE " ;
 cout<<"\n 1. Insert in the tree ";
 cout<<"\n 2. Delete a node from the tree";
 cout<<"\n 3. Search for an element in the tree";
 cout<<"\n 4. Display the tree ";
 cout<<"\n 5. Exit " ;
 cout<<"\nEnter Your Choice: ";
 cin>>ch;
 switch(ch)
 {
 case 1 : obj.insert();
 cout<<"\nNode Inserted.\n";
 break;
 case 2 : obj.del();
 break;
 case 3 : obj.search();
 break;
 case 4 : obj.disp();
 break;
 case 5 : y=1;
 break;
 default : cout<<"\nEnter a Valid Choice.";
 }
 cout<<endl;

 }while(y!=1);
 return 1;
 }
 */





class BST
{
public:
    /*struct edge_compare {
        double compareAt;
        double getPriority(const Edge & e)
        {
            Vertex start=*(e.p_start);
            Vertex end=*(e.p_twin->p_start);
            if(end.coord.y==start.coord.y)
                return start.coord.x;
            double r=(end.coord.y-start.coord.y);
            //cout<<e.myaddr<<"PRiority---> "<<r<<endl;

            return (((compareAt-start.coord.y)*(end.coord.x-start.coord.x))/r)+start.coord.x;

        }
    } comp;*/
    //vector<Edge> S;
    //set<Edge, edge_compare> S;
    RBtree S;
    unordered_map<int,Vertex> helper;

public:


    void insert(Edge e,Vertex v)
    {
        S.compareAt=v.coord.y; //use this
        //S.push_back(e);

        S.insert(e);
    }
    void setHelper(Edge e,Vertex v)
    {
        helper[e.myaddr]=v;
    }
    void remove(Edge e)
    {
        S.compareAt=e.p_twin->p_start->coord.y;
        //for(vector<Edge>::iterator it=S.begin();it!=S.end();it++)
        //  if(*it==e)
        //{
        //  S.erase(it);
        //break;

        //}
        S.del(e);
    }
    Edge find(Vertex v)
    {
        //cout<<"Reached hurray\n"<<endl;
        S.compareAt=v.coord.y;
        Edge e;
        Edge etwin;
        etwin.p_start=&v;
        e.p_twin=&etwin;
        e.p_start=&v;
        //set<Edge,edge_compare>::iterator it=S.lower_bound(e);
        S.insert(e);
        node *newnode=S.get(e);
        node * predes= S.pred(newnode);
        S.del(e);
        //comp.getPriority(e);
        //cout<<"HELPER RETURNED FOR "<<v.myaddr<<"is-->";
        //cout<<it->myaddr<<endl;
        if(predes==NULL)
            return (S.least())->e;
        return predes->e;

        //        vector<Edge>::iterator i=S.end();
        //        for(vector<Edge>::iterator it=S.begin();it!=S.end();it++)
        //        {
        //            cout<<it->myaddr<<"<=====present in list now\n";
        //            if(comp.getPriority(*it)<comp.getPriority(e))
        //            {
        //                if(i==S.end())
        //                   i=it;
        //                if(comp.getPriority(*i)<comp.getPriority(*it))
        //                    i=it;
        //                cout<<"works on "<<it->myaddr<<endl;
        //                cout<<"currently holding"<<i->myaddr<<endl;
        //            }
        //        } cout<<"Just bwfore\n";
        //            cout<<i->myaddr<<endl;
        //        if(i==S.end())
        //        {
        //            return *(S.rbegin());
        //        }
        //        else
        //        {
        //
        //            return *i;
        //        }
    }
};
#endif
