#include<iostream>
using namespace std;

class DisjSets{
private:
	int *parent = NULL;
	int *rank = NULL;
	int length;

public:
	DisjSets(int numOfElem){
		length = numOfElem;
		parent = new int[numOfElem];
		rank = new int[numOfElem];
		
		for(int i=0;i<numOfElem;i++){
			rank[i] = 0;
			parent[i] = -1;
		}
		
	}
	void makeSet(int v){
		parent[v] = v;
		rank[v] = 0;
	}

	int findSet(int v){
		if(parent[v] == v)
			return v;
		else 
			return parent[v] = findSet(parent[v]);
	}

	void Union(int a, int b){
		
		if (parent[a]  == -1 || parent[b] == -1){
			cout<<"Union failed!"<<endl;
			return;
		}

		a = findSet(a);
		b = findSet(b);

		if(a!=b){
			if(rank[a]<rank[b])
				swap(a,b);
			parent[b] = a;
			if(rank[a] == rank[b])
				rank[a]++;
		}
	}

	void print(int x){
		
		if(parent[x] == -1){
			cout<<"There's no set containing "<<x<<endl;
			return;
		}

		int rootx = findSet(x);

		for(int i = 0; i < length; i++){
			if (parent[i] == -1)
				continue;
			
			int rooti = rootx;

			if (parent[i] != rootx)
				rooti = findSet(i);

			if(rooti == rootx)
				cout<<i<<" ";
		}
		cout<<endl;
	}

	~DisjSets(){
		delete[] parent;
		delete[] rank;
	}

};

int main(){
	DisjSets ds(100);

	while(true){
		cout<<"1. Make Set "<<endl;
		cout<<"2. Find Set "<<endl;
		cout<<"3. Union "<<endl;
		cout<<"4. Print "<<endl;
		cout<<"5. Quit "<<endl;
		cout<<">> ";

		int choice,n,m;
		cin>>choice;
		if(choice == 5)
			break;
		else if (choice == 1){
			cout<<"Enter the element: ";
			cin>>n;
			ds.makeSet(n);
		} else if (choice == 2){
			cout<<"Enter the element: ";
			cin>>n;
			cout<<"Root: "<<ds.findSet(n)<<endl;
		} else if (choice == 3){
			cout<<"Enter the elements: ";
			cin>>n>>m;
			ds.Union(n,m);
		} else if (choice == 4){
			cout<<"Enter the element: ";
			cin>>n;
			cout<<"Elements of the set containing "<<n<<" : ";
			ds.print(n);
		}
	}
}
//Nishan Test Case
//1 1 1 2 1 3 1 4 1 5 3 2 3 3 4 5 3 4 1 3 4 2

//Kashem Sir Slide
//1 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8
//3 2 1 3 2 3 3 2 4 3 3 5 3 3 6 3 5 7 3 6 8