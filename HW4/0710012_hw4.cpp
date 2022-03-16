#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ofstream output;
vector <int> out;
bool conflict=false;

struct Vertex
{
    int key;
    int color;    //white=0, gray=1, black=2
    Vertex *parent;
    vector <int> near;
};

vector <Vertex> arr;

void DFS_VISIT(Vertex &u){
    u.color=1;

    for(int i=0;i<u.near.size();i++){
        if(arr[u.near[i]].color==1){
            //cout << "hello"<<u.near[i];
            conflict=true;
            return;
        }
        if(arr[u.near[i]].color==0){
            arr[u.near[i]].parent=&u;
            DFS_VISIT(arr[u.near[i]]);
        }
    }
    u.color=2;
    out.push_back(u.key);
}

void DFS(){
    for(int i=0;i<arr.size();i++){
        arr[i].color=0;
        arr[i].parent=NULL;
    }
    for(int i=0;i<arr.size();i++){
        if(arr[i].color==0){
            DFS_VISIT(arr[i]);
            //cout << "ad"<<arr[i].key;
        }
        if(conflict)return;
    }
}



int main(int argc, char** argv){
    ifstream input(argv[1]);
    output.open(argv[2]);

    int num, a, b, a_i=-1, b_i=-1;
    input>>num;


    for(int i=0;i<num;i++){
        Vertex *temp = new Vertex();
        temp->key=i;
        arr.push_back(*temp);
    }

    while(input>>a>>b){
        arr[b].near.push_back(a);
    }

    
    /*for(int i=0;i<arr.size();i++){
        cout << "\n"<<arr[i].key<<endl;
        for(int j=0;j<arr[i].near.size();j++){
            cout << arr[arr[i].near[j]].key<< " ";
        }
        cout << endl;
    }*/

    DFS();

    if(conflict)
        output<<"Conflict";
    else
        for(int i=out.size()-1;i>=0;i--)
            output<<out[i]<<" ";


    input.close();
    output.close();
    
    return 0;
}
