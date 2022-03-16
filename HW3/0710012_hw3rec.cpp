#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

ofstream output;
string x,y;

int Recursive(int i, int j){
    if(i==0 || j==0)return 0;
    if(x[i-1]==y[j-1])
        return Recursive(i-1,j-1)+1;
    else if(Recursive(i-1,j)>=Recursive(i,j-1))
        return Recursive(i-1,j);
    else return Recursive(i,j-1);
}
void PRINT(int i, int j){
    if(i==0 || j==0)return;
    if(x[i-1]==y[j-1]){
        PRINT(i-1,j-1);
        output<<x[i-1];
    }
    else if(Recursive(i-1,j)>=Recursive(i,j-1)){
        PRINT(i-1,j);
    }
    else PRINT(i,j-1);
}


int main(int argc, char** argv){

    ifstream input(argv[1]);
    output.open(argv[2]);

    getline(input,x);
    getline(input,y);
    int n=x.length();
    int m=y.length();

    PRINT(n,m);

    input.close();
    output.close();
    
    return 0;
}