#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <math.h>
using namespace std;

enum Color {RED, BLACK};

class Node
{
    public:
    int data,people;///people的部分要在全看過
    bool color;
    set<int> *ID;
    Node *left, *right, *parent;
    Node(){
        color=RED;
        data=0;people=1;
    }
};

class RBTree{
    public:
    Node *root;
    Node *nil;
    RBTree(){
        nil=new Node();
        nil->color=BLACK;
        root=nil;
        root->parent=nil;
        nil->people=0;
    }

    void INORDER_TREE_WALK(Node *x){
        if (x!=nil){
            INORDER_TREE_WALK(x->left);
            cout << x->data << " ";
            INORDER_TREE_WALK(x->right);
        }
        
    }

    void LEFT_ROTATE(Node *x){
        if(x->right==nil)return;
        Node *y=x->right;
        x->right=y->left;
        if(y->left!=nil)
            (y->left)->parent=x;
        
        y->parent=x->parent;
        
        if(x->parent==nil)
            root=y;
        else
            if (x==(x->parent)->left)
                (x->parent)->left=y;
            else
                (x->parent)->right=y;
        
        y->left=x;
        x->parent=y;    
        y->people=x->people;
        x->people=x->left->people+x->right->people+x->ID->size();
    }
    void RIGHT_ROTATE(Node *x){
        if(x->left==nil)return;
        Node *y=x->left;
        x->left=y->right;
        if(y->right!=nil)
            (y->right)->parent=x;
        
        y->parent=x->parent;
        
        if(x->parent==nil)
            root=y;
        else
            if (x==(x->parent)->left)
                (x->parent)->left=y;
            else
                (x->parent)->right=y;
        
        y->right=x;
        x->parent=y; 
        y->people=x->people;
        x->people=x->left->people+x->right->people+x->ID->size();
    }

    Node* successor(Node *z){//一定有右樹
        Node *x=z->right;
        while(x->left!=nil)
            x=x->left;
        return x;
    }

    Node* RB_Select(Node* n, int i){    //retrun node
        //if(i>root->people)return RB_Select(root,root->people);
        int m=n->right->people+1;
        int k=n->right->people+n->ID->size();
        if(i==m)return n;
        else if(i>m&&i<=k)return nil;
        else if(i>k)return RB_Select(n->left,i-k);
        else return RB_Select(n->right,i);
    }

    int RB_Rank(int idata){        //return 排名
        Node *p;
        Node* y= RB_Search(idata, &p);
        int r=y->left->people+y->ID->size();
        while(y!=root){
            if(y==y->parent->right)
                r+=y->parent->left->people+y->parent->ID->size();
            y=y->parent;
        }
        return r;
    }

    Node* RB_Search(int sdata, Node** p){
        *p=nil;
        Node *x=root;
        while (x!=nil)
        {
            *p=x;
            if(sdata==x->data){return x;}
            if(sdata<x->data)
                x=x->left;
            else
                x=x->right;
        }
        return nil;
    }

    void RB_Insert(int iID,int iData){
        Node *p;
        Node *y=RB_Search(iData, &p);
        if(y!=nil){
            y->ID->insert(iID);
            while (y!=nil){
                y->people++;
                y=y->parent;
            }
            return;
        }else{
            Node *temp;
            temp=new Node();
            temp->data=iData;
            temp->ID = new set<int>;
            temp->ID->insert(iID);
            temp->parent=p;
            temp->left=nil;
            temp->right=nil;
            temp->people=1;
            if(p==nil){
                root=temp;
            }
            else if(p->data>temp->data){p->left=temp;}
            else{p->right=temp;}
            Node *fix_p=temp;
            while (fix_p!=nil){
                fix_p->people=fix_p->left->people+fix_p->right->people+fix_p->ID->size();
                fix_p=fix_p->parent;
            } 
            InsertFixedUpRBT(temp);
        } 
    }

    void InsertFixedUpRBT(Node* z){
        Node *y;
        while ((z->parent)->color==RED){
            if(z->parent==((z->parent)->parent)->left){
                y=((z->parent)->parent)->right;
                if(y->color==RED){              //case 1
                    z->parent->color=BLACK;
                    y->color=BLACK;
                    z->parent->parent->color=RED;
                    z=z->parent->parent;
                }
                else{
                    if(z==z->parent->right){
                        z=z->parent;
                        LEFT_ROTATE(z);
                    }
                    z->parent->color=BLACK;
                    z->parent->parent->color=RED;
                    RIGHT_ROTATE(z->parent->parent);
                }
            }
            else {
                y=((z->parent)->parent)->left;
                if(y->color==RED){              //case 1
                    z->parent->color=BLACK;
                    y->color=BLACK;
                    z->parent->parent->color=RED;
                    z=z->parent->parent;
                }
                else{
                    if(z==z->parent->left){
                        z=z->parent;
                        RIGHT_ROTATE(z);
                    }
                    z->parent->color=BLACK;
                    z->parent->parent->color=RED;
                    LEFT_ROTATE(z->parent->parent);
                }
            }
        }
        root->color=BLACK;
    }

    void RB_Delete(int dID,int dData){
        Node *p;
        Node *z=RB_Search(dData, &p);
        if(z==nil)return;
        else if(z->ID->size()>1){
            z->ID->erase(dID);
            while(z!=nil){
                z->people--;
                z=z->parent;
            }
            return;
        }else{
            Node *x,*y;
            if(z->left==nil||z->right==nil){
                y=z;}
            else
                y=successor(z);

            if(y->left!=nil)
                x=y->left;
            else{
                x=y->right;}

            x->parent=y->parent;
            if(y->parent==nil)
                root=x;
            else if(y==(y->parent)->left){
                (y->parent)->left=x;}
            else
                (y->parent)->right=x;

            if(y!=z){
                z->data=y->data;
                delete z->ID;
                z->ID=y->ID;
            }
            nil->people=0;
            Node* fix_p=x->parent;
            while (fix_p!=nil){
                fix_p->people=fix_p->left->people+fix_p->right->people+fix_p->ID->size();
                fix_p=fix_p->parent;
            }
            if (y->color==BLACK){
                DeleteFixedUpRBT(x);}
            delete y;
        }
    }

    void DeleteFixedUpRBT(Node* x){
        Node* w;
        while(x!=root&&x->color==BLACK){
            if(x==x->parent->left){
                w=x->parent->right;
                if(w->color==RED){                                  //case1
                    w->color=BLACK;
                    x->parent->color=RED;
                    LEFT_ROTATE(x->parent);
                    w=x->parent->right;
                }
                if(w->left->color==BLACK&&w->right->color==BLACK){
                    w->color=RED;                                   //case2
                    x=x->parent;
                }
                else{
                    if(w->right->color==BLACK){
                        w->left->color=BLACK;
                        w->color=RED;
                        RIGHT_ROTATE(w);
                        w=x->parent->right; 
                    }
                    w->color=x->parent->color;
                    x->parent->color=BLACK;
                    w->right->color=BLACK;
                    LEFT_ROTATE(x->parent);
                    x=root;
                }
            }
            else{
                w=x->parent->left;
                if(w->color==RED){                                  //case1
                    w->color=BLACK;
                    x->parent->color=RED;
                    RIGHT_ROTATE(x->parent);
                    w=x->parent->left;
                }
                if(w->right->color==BLACK&&w->left->color==BLACK){
                    w->color=RED;                                   //case2
                    x=x->parent;
                }
                else{
                    if(w->left->color==BLACK){
                        w->right->color=BLACK;
                        w->color=RED;
                        LEFT_ROTATE(w);
                        w=x->parent->left; 
                    }
                    w->color=x->parent->color;
                    x->parent->color=BLACK;
                    w->left->color=BLACK;
                    RIGHT_ROTATE(x->parent);
                    x=root;
                }
            }
        }
        x->color=BLACK;
    }
};

int main(int argc, char** argv){
    RBTree Pokemon;
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    Node *nmin,*nmax,*n,*p;
    bool no=0;
    char c;
    while(input>>c){
        int n1, n2,m1,m2;
        //Pokemon.INORDER_TREE_WALK(Pokemon.root);
        //cout <<"\n"<<Pokemon.root->data<< endl;
        switch (c){ 
            case 'I':
                input >> n1 >> n2;
                Pokemon.RB_Insert(n1,n2);
                break;
            case 'D':
                //output<<"d";
                input >> n1 >> n2;
                Pokemon.RB_Delete(n1,n2);
                break;
            case 'R':///////////有問題
                input >> n1;
                n=Pokemon.RB_Select(Pokemon.root,n1);
                if(n!=Pokemon.nil){
                    output<<"R "<<*n->ID->begin()<<" "<<n->data<<endl;
                }
                else output<< "R 0"<<endl;
                break;
            case 'V':
                input >> n1;
                output<<"V "<< Pokemon.root->people-Pokemon.RB_Rank(n1)+1<<endl;////////////
                break;
            case 'B':
                input >> n1 >> n2;
                no=0;
                m1=min(n1,n2);m2=max(n1,n2);
                nmax=Pokemon.RB_Search(m2,&p);
                nmin=Pokemon.RB_Search(m1,&p);
                while (nmin==Pokemon.nil||nmax==Pokemon.nil){
                    if(nmin==Pokemon.nil){
                        m1++;
                        nmin=Pokemon.RB_Search(m1,&p);
                    }
                    if(nmax==Pokemon.nil){
                        m2--;
                        nmax=Pokemon.RB_Search(m2,&p);
                    }
                    if(m2<m1){output<<"B 0"<<endl;no=1;break;}
                }
                if(!no)
                    output<<"B "<< Pokemon.root->people-Pokemon.RB_Rank(nmax->data)+1
                    <<" " << Pokemon.root->people-Pokemon.RB_Rank(nmin->data)+1<<endl;
                break;
            case 'A':  
                input >> n1 >> n2;
                if(min(n1,n2)>Pokemon.root->people){output<<"A 0"<<endl;break;}
                m1=min(n1,n2);
                m2=max(n1,n2);
                if(m2>Pokemon.root->people)m2=Pokemon.root->people;
                nmin=Pokemon.RB_Select(Pokemon.root,m2);
                nmax=Pokemon.RB_Select(Pokemon.root,m1);
                while(nmin==Pokemon.nil){
                    m2--;
                    nmin=Pokemon.RB_Select(Pokemon.root,m2);
                }
                while(nmax==Pokemon.nil){
                    m1++;
                    nmax=Pokemon.RB_Select(Pokemon.root,m1);
                }
                output<<"A "<< *(nmax->ID->begin()) << " "<<nmax->data<<" "
                            << *(nmin->ID->begin()) << " "<<nmin->data<<endl;///////////////
                break;
            
            default:
                break;
        }
    }

    input.close();
    output.close();
    
    return 0;
}