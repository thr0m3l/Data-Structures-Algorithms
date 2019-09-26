#include<iostream>
#include<random>
using namespace std;

random_device rd;
mt19937 gen(rd());


void activity_selector(int s[], int f[], int n){
	cout<<"\nOptimal Solution: \n";
	cout<<s[0]<<" "<<f[0]<<endl;

	int k = 1;
	int count = 1;
	for (int m = 1; m<n; m++){
		if(s[m] >= f[k]){
			cout<<s[m]<<" "<<f[m]<<endl;
			k = m;
			count++;
		}
	}
	cout<<"No. of selected activities: "<<count<<" out of "<<n<<endl;
}

int Partition(int arr[], int arr2[],int low, int high ){
    int pivot = arr[high];


    int i = low - 1;
    for(int j = low ; j < high; j++){
        if(arr[j] <= pivot){
            i++;
            swap(arr[i],arr[j]);
            swap(arr2[i],arr2[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    swap(arr2[i+1],arr2[high]);

    return i + 1;
}

void QuickSort(int arr[], int arr2[],int low, int high){
    if (low<high){
        int q = Partition(arr, arr2, low, high);
        QuickSort(arr, arr2, low,q-1);
        QuickSort(arr, arr2, q+1, high); 
    }
}

void generator(int s[],int f[], int n){

	uniform_int_distribution<> dis(-n*10, n*10);

	for(int i = 0; i < n ; i++){
		f[i] = abs(dis(gen));
		s[i] = abs(dis(gen));
		if (s[i] > f[i])
			swap(s[i],f[i]);
	}

	QuickSort(f,s,0,n-1);

}


int main(){
	int n;
	cout<<"Number of activities: ";
	cin>>n;

	int s[n],f[n];
	generator(s,f,n);
	cout<<"Activities: \n";
	for(int i = 0; i < n; i++){
		cout<<s[i]<<" "<<f[i]<<endl;
	}
	activity_selector(s,f,n);

	return 0;
}

/*
11
1 4
3 5
0 6
5 7
3 9
5 9
6 10
8 11
8 12
2 14
12 16
*/
