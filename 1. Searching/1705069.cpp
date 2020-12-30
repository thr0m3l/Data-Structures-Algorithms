#include<chrono>
#include<iostream>
#include<cstdlib>
using namespace std;
using namespace std::chrono;


long long avgtime = 0, avgtime1 = 0, avgavg = 0;
int non_zero = 0;
void bubbleSort(int arr[],int n){
	auto start = high_resolution_clock::now();
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(arr[i]>arr[j]){
				swap(arr[i],arr[j]);
			}
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start); 
	cout <<"Runtime: "<< duration.count() <<" nanoseconds" << endl;
}

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; 
    j = 0;  
    k = l;  
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  

void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    {  
        int m = l+(r-l)/2; 
  
         
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

int linearSearch(int arr[], int n, int elem){
	
	auto start = high_resolution_clock::now();
	for(int i = 0 ; i<n ; i++){
		if(arr[i] == elem){
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<nanoseconds>(stop - start); 
			if(duration.count() != 0) {
				cout <<"Runtime: "<< duration.count() <<" nanoseconds" << endl;
				avgtime += duration.count();
			}
			return i;
		}
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start); 
	if(duration.count() != 0) {
		cout <<"Runtime: "<< duration.count() <<" nanoseconds" << endl;
		avgtime += duration.count();
		non_zero++;
	}
	
	return -1;
}

int binarySearch(int arr[], int l, int r, int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2;       
        if (arr[mid] == x) 
            return mid;  
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x); 
    }  
    return -1; 
} 

int myBinarySearch(int arr[], int n, int elem){
	mergeSort(arr,0,n);

	auto start = high_resolution_clock::now();
	// int result =  binary_search(arr, arr+n, elem);
	int result = binarySearch(arr, 0, n, elem);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start); 
	if(duration.count())cout <<"Runtime: "<< duration.count() <<" nanoseconds" << endl;
	avgtime1 += duration.count();	
	return result;
}

int main(){
	int size;
	cin>>size;
	srand(1);
	
	int randomArray2[size] = {0};
	srand(1);
	for(int j=0;j<100000;j++){
		for(int i=0;i<size;i++){
			randomArray2[i] = rand();
	}
	cout<<linearSearch(randomArray2,size,rand())<<endl;
	// cout<<myBinarySearch(randomArray2,size,rand())<<endl;
	}
	cout<<avgtime/100000.0<<endl;
	// cout<<avgtime1/100000.0<<endl;
	
}
