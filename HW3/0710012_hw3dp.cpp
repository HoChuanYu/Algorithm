#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

ofstream output;
vector<vector<int>> c;
string x,y;

void PRINT(int i, int j){
    if(i==0 || j==0)return;
    if(x[i-1]==y[j-1]){
        PRINT(i-1,j-1);
        output<<x[i-1];
    }
    else if(c[i-1][j]>=c[i][j-1]){
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
    for(int i=0;i<=n;i++){
        c[i].resize(m+1);
        for(int j=0;j<=m;j++){
            c[i][j]=0;
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1])c[i][j]=c[i-1][j-1]+1;
            else if(c[i-1][j]>=c[i][j-1])c[i][j]=c[i-1][j];
            else c[i][j]=c[i][j-1];
        }
    }
    x=s1;
    y=s2;
    PRINT(n,m);

    input.close();
    output.close();

    return 0;
}