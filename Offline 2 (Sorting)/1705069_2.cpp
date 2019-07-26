#include<iostream>
#include<chrono>
#include<cmath>
using namespace std;
using namespace std::chrono;

void powerSet(char* set, long long size){
	long long psize = pow(2,size);

	auto start = high_resolution_clock::now();
	for(long long i=0;i<psize;i++){
		cout<<i<<" : ";
		long long temp = i;
		for(long long j = 0; j<size;j++){
			if(temp&1){
				cout<<set[j];
			}
			temp = temp>>1;
		}
		cout<<endl;
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);
	cout<<"Runtime: "<<duration.count()<<" nanoseconds"<<endl;
}

int main(){
	cout<<"Number of elements in the set: ";
	long long size;
	cin>>size;
	srand(1);
	char set[size];
	cout<<"Randomly generating a set. . . "<<endl;
	for(long long i=0;i<size;i++){
		// cin>>set[i];
		int r = rand();
		if(r%3 == 0){
			set[i] = 'a' + rand() % 26;
		} else if (r%3 == 1){
			set[i] = 'A' + rand() % 26;
		} else {
			set[i] = '0' + rand() % 10;
		}

	}
	set[size] = 0;
	cout<<"Generated Set: "<<set<<endl;
	powerSet(set,size);
}