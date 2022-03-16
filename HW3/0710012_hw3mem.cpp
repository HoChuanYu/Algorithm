#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

ofstream output;
string x,y;
vector<vector<int>> c;

int Mem(int i, int j){
    if(c[i][j]!=-1)return c[i][j];
    if(i==0 || j==0){c[i][j]=0;return 0;}
    if(x[i-1]==y[j-1]){
        c[i][j]=Mem(i-1,j-1)+1;
        return c[i][j];
    }
    else if(Mem(i-1,j)>=Mem(i,j-1)){
        c[i][j]=Mem(i-1,j);
        return c[i][j];
    }
    else {
        c[i][j]=Mem(i,j-1);
        return c[i][j];
    }
}
void PRINT(int i, int j){
    if(i==0 || j==0)return;
    if(x[i-1]==y[j-1]){
        PRINT(i-1,j-1);
        output<<x[i-1];
    }
    else if(Mem(i-1,j)>=Mem(i,j-1)){
        PRINT(i-1,j);
    }
    else PRINT(i,j-1);
}

int main(int argc, char** argv){
    ifstream input(argv[1]);
    output.open(argv[2]);

    int n,m;
    string s1,s2;
    getline(input,s1);
    getline(input,s2);
    n = s1.length(); m = s2.length();
    
    c.resize(n+1);
    for(int i=0;i<n+1;i++){
        c[i].resize(m+1);
        for(int j=0;j<=m;j++){
            c[i][j]=-1;
        }
    }

    x=s1;
    y=s2;
    PRINT(n,m);

    input.close();
    output.close();

    return 0;
}