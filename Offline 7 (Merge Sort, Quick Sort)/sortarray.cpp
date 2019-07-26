#include <cstdio>
#include<iostream>
#include<chrono>
#include<random>

#define INFINITY 2147483647

using namespace std;

void Merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1+1], R[n2+1]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; 
    j = 0;  
    
    L[n1] = INFINITY;
    R[n2] = INFINITY;
    for (k = l; k<r; k++){
        if(L[i] < R[j])
            arr[k] = L[i++];
        else
            arr[k] = R[j++];
    }
} 
  

void MergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    {  
        int m = (l+r)/2; 
        MergeSort(arr, l, m); 
        MergeSort(arr, m+1, r); 
        Merge(arr, l, m, r); 
    } 
}

int Partition(int arr[], int low, int high ){
    int pivot = arr[high];

    int i = low - 1;
    for(int j = low ; j < high; j++){
        if(arr[j] <= pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);

    return i + 1;
}

void QuickSort(int arr[], int low, int high){
    if (low<high){
        int q = Partition(arr, low, high);
        QuickSort(arr,low,q-1);
        QuickSort(arr, q+1, high); 
    }
}

int main()
{
    int choice, n;

    random_device rd;
    mt19937 gen(rd()); 
    uniform_int_distribution<> dis(1, 10000);
    
    int arr[1000];
    for (int n=0; n<1000; n++){
        arr[n] = dis(gen);
    }

    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            break;

        case 2:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            break;

        case 3:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            break;

        case 4:
            printf("Applying merge sort\n");
            MergeSort(arr,0,999);
            printf("Time taken to finish: <your time>\n");
            break;

        case 5:
            printf("Applying quicksort\n");
            QuickSort(arr,0,999);
            printf("Time taken to finish: <your time>\n");
            break;

        case 6:
            printf("Array: ");
            for (int i=0; i<1000; i++){
                cout<<arr[i]<<" "; 
            }
            cout<<endl;
            break;
        }
    }
}

