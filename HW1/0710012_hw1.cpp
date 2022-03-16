#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
#include <iomanip>
#define MAX 0x3f3f3f3f

using namespace std;

struct Way{
	int ID1;
	int ID2;
	double dis;
};

void MERGE(vector<Way> &A, int p, int q, int r){
	int n1=q-p+1;						
	int n2=r-q;
	vector<Way> L,R;
	L.resize(n1+1);R.resize(n2+1);
	for(int i=0;i<n1;i++){
		L[i]=A[p+i];
	}
	for(int i=0;i<n2;i++){
		R[i]=A[q+i+1];
	}
	
	L[n1].dis=MAX;R[n2].dis=MAX;
	
	int a=0, b=0;
	for(int i=p;i<=r;i++){
		if(L[a].dis<R[b].dis || (L[a].dis==R[b].dis&&L[a].ID1<R[b].ID1) ||
		 (L[a].dis==R[b].dis&&L[a].ID1==R[b].ID1&&L[a].ID2<=R[b].ID2)){
			A[i]=L[a];
			a++;
		}
		else{ 
			A[i]=R[b];
			b++;
		}
	}
}

void MERGE_SORT(vector<Way> &A, int p, int r){
	if(p<r){
		int q = floor((p+r)/2);
		MERGE_SORT(A,p,q);
		MERGE_SORT(A,q+1,r);
		MERGE(A,p,q,r);
	}
}

int main (int argc,char** argv) {
	ifstream input(argv[1]);
	ofstream output(argv[2]);
	
	int num;
	input >> num;
	
	int id[num];
	double x[num], y[num];
	
	for(int i=0;i<num;i++){
		input>>id[i];
		input>>x[i];
		input>>y[i];
	}
	
	int mode,count=0,index=0;
	int total=num*(num-1)/2;
	vector<Way> disarr;
	input>> mode;
	switch(mode){
		case 1:
			double D;
			input >> D;
			for(int i=0;i<num-1;i++){
				for(int j=i+1;j<num;j++){
					Way temp;
					temp.dis=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
					temp.ID1=min(id[i],id[j]);
					temp.ID2=max(id[i],id[j]);
					disarr.push_back(temp);
				}
			}
			
			MERGE_SORT(disarr,0,disarr.size()-1);
			while(disarr[index].dis<D){
				count++;
				index++;
				if(index>=total)
					break;
			}
			index=0;
			output<<count<<endl;
			while(disarr[index].dis<D){
				output<<disarr[index].ID1<<" "<<disarr[index].ID2<<" "
				<<fixed <<setprecision(3)<<disarr[index].dis<<endl;
				index++;
				if(index>=total)
					break;
			}
	
			break;
			
		case 2:
			int N;
			input >> N;
			output<<N<<endl;
			for(int i=0;i<num-1;i++){
				for(int j=i+1;j<num;j++){
					Way temp;
					temp.dis=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
					temp.ID1=min(id[i],id[j]);
					temp.ID2=max(id[i],id[j]);
					disarr.push_back(temp);
				}
			}
			
			MERGE_SORT(disarr,0,disarr.size()-1);
			
			for(int i=0;i<N;i++)
				output<<disarr[i].ID1<<" "<<disarr[i].ID2<<" "
				<<fixed <<setprecision(3)<<disarr[i].dis<<endl;
				
			break;
			
		case 3:
			int ID1,ID2;
			double dis,small=MAX;
			for(int i=0;i<num-1;i++){
				for(int j=i+1;j<num;j++){
					dis=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
					if(small>dis){
						small=dis;
						ID1=min(id[i],id[j]);
						ID2=max(id[i],id[j]);
					} 
					else if(small==dis){
						if(ID1>min(id[i],id[j])){
							ID1=min(id[i],id[j]);
							ID2=max(id[i],id[j]);
						}
					}
				}
			}
			output<<"1\n"<<ID1<<" "<<ID2<<" "<<fixed <<setprecision(3)<<small;
			break;
	}
	input.close();
	output.close();
	
  	return 0;
}
