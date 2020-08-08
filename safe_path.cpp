// Develope Algorithm to get path b/w two point such that passenger tarvel through least covid-19 
//containment zone with minimum cost 
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
class safest_path{
	private:	int n;                            // n is number of nodes
                int m;                            //m is the no of path 
				int a[1024],vi[1024],dan[1024],cost[1024],path[1024];
				vector<pair<int,int>>b[1024];       //store the graph in matrix form
	public:		safest_path(int p=0,int q=0){
					n=p;
					m=q;
				}
				void intiliase();               //used to intialise the array
				void cost_path();               //used to create graph
				void solve();                     
				int danger();                   // calculate the danger of passenger
				int min_cost();                 //calculate min cost
				void req_path();                //give the path
	};
	void safest_path::intiliase(){
		for(int i=0;i<n;i++){
		//	cout<<"enter No of corona case in node "<<i+1<<" ";
			cin>>a[i];
			vi[i]=0;
			cost[i]=INT_MAX;                   // Intialise as infinite
			dan[i]=INT_MAX;
		}
	}
	void safest_path::cost_path(){
		int p,q,k;
		for(int i=0;i<m;i++){
			cin>>p>>q>>k;
			b[p-1].push_back(make_pair(q-1,k));
			b[q-1].push_back(make_pair(p-1,k));
		}
	}
	void safest_path::solve(){
		vector<int>v;
		v.push_back(n-1);
		vi[n-1]=1;
		dan[n-1]=a[n-1];
		cost[n-1]=0;
		for(int i=0;i<v.size();i++){
			int k=v[i];
			for(int j=0;j<b[k].size();j++){
				int p=b[k][j].first;
				if(vi[p]==0){
					v.push_back(p);
					vi[p]=1;
				}
				if(dan[p]>dan[k]+a[p]){
					dan[p]=dan[k]+a[p];
					cost[p]=cost[k]+b[k][j].second;
					path[p]=k;
				}
				else if(dan[p]==dan[k]+a[p]){
					if(cost[p]>cost[k]+b[k][j].second){
						path[p]=k;
						cost[p]=cost[k]+b[k][j].second;
					}
					cost[p]=min(cost[p],cost[k]+b[k][j].second);
				}
			}
		}
	}
	int safest_path::danger(){
		return dan[0];
	}
	int safest_path::min_cost(){
		return cost[0];
	}
	void safest_path::req_path(){
		int p=0;
		while(1){
			cout<<p+1<<"->";
			p=path[p];
			if(p==n-1){
				break;
			}
		}
		cout<<p+1;
	}
int main() {
	int p,q;
	cout<<"Enter No of Nodes"<<endl;
	cin>>p;
	cout<<"Enter No of  path"<<endl;
	cin>>q;
	safest_path ob(p,q);
	ob.intiliase();
	ob.cost_path();
	ob.solve();
	cout<<"minimum danger="<<ob.danger()<<endl;
	cout<<"minimum cost="<<ob.min_cost()<<endl;
	ob.req_path();
	return 0;
}