#include<iostream>
#include<chrono>
using namespace std;
using namespace std::chrono;


long long selection_sort(long arr[], int size){
	auto start = high_resolution_clock::now();
	for(int i =0; i<size-1;i++){
		for(int j=i+1;j<size;j++){
			if(arr[i]>arr[j]){
				swap(arr[i],arr[j]);
			}
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start); 
	
	return (long long)duration.count();
}

long long insertion_sort(long arr[],int size){
	auto start = high_resolution_clock::now();
	int i, key, j;  
    for (i = 1; i < size; i++) 
    {  
        key = arr[i];  
        j = i - 1;  
        while (j >= 0 && arr[j] > key) 
        {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start); 
	return (long long)duration.count();
}
void generate(long arr[],int size, int mode = 0){
	//For sorted, mode = 1
	//For unsorted, mode = 0 (default)
	//For reversely sorted, mode = 2
	
	if (mode == 0){
		for(int i = 0;i<size;i++){
			arr[i] = rand();
		}
	} else if(mode == 1){
		arr[0] = 0;
		for(int i = 1; i<size;i++){
			long max = i*1000;
			long min = (i - 1)*1000;
			arr[i] = (long)(((double) rand() / (RAND_MAX+1)) * (max-min+1) + min);
		}
	} else if(mode == 2){
		arr[size-1] = 0;
		for(int i = size - 2; i>=0; i--){
			long max = (size - i)*1000;
			long min = (size - i - 1)*1000;
			arr[i] = (long)(((double) rand() / (RAND_MAX+1)) * (max-min+1) + min);
		}
	}	
}

void print_arr(long arr[], int size){
	for(int i =0; i<size; i++){
		cout<<i<<" : "<<arr[i]<<endl;
	}
}

void copy_arr(long arr[], long arr2[], int size){
	for(int i=0;i<size;i++){
		arr2[i] = arr[i];
	}
}

int main(){
	cout<<"Please input array size: ";
	int size;
	cin>>size;
	long randArr[size] = {0}, randArr2[size] = {0}, randArr3[size] = {0},
	 copyRandArr[size] = {0},
	copyRandArr2[size] = {0},copyRandArr3[size] = {0};
	srand(1);

	cout<<"Number of iterations:  ";
	int itr;
	cin>>itr;

	long long ins_avg = 0,ins_best = 0,ins_worst = 0, sel_avg = 0,sel_best = 0, sel_worst = 0;

	for(int i = 0; i<itr; i++){
		generate(randArr,size);
		generate(randArr2,size,1);
		generate(randArr3,size,2);

		copy_arr(randArr,copyRandArr,size);
		copy_arr(randArr2,copyRandArr2,size);
		copy_arr(randArr3,copyRandArr3,size);

		ins_avg += insertion_sort(randArr,size); //Average case
		ins_best += insertion_sort(randArr2,size); //Best case
		ins_worst += insertion_sort(randArr3,size); //Worst case

		sel_avg += selection_sort(copyRandArr,size); //Average case
		sel_best += selection_sort(copyRandArr2,size); //Best case
		sel_worst += selection_sort(copyRandArr3,size); //Worst case
	}
	cout<<"For Insertion Sort : "<<endl;
	cout<<"Best case: "<<ins_best*1.0/itr<<" nanoseconds"<<endl;
	cout<<"Average case: "<<ins_avg*1.0/itr<<" nanoseconds"<<endl;
	cout<<"Worst case: "<<ins_worst*1.0/itr<<" nanoseconds"<<endl;

	cout<<"For Selection Sort : "<<endl;
	cout<<"Best case : "<<sel_best*1.0/itr<<" nanoseconds"<<endl;
	cout<<"Average case : "<<sel_avg*1.0/itr<<" nanoseconds"<<endl;
	cout<<"Worst case: "<<sel_worst*1.0/itr<<" nanoseconds"<<endl;

	return 0;
}
