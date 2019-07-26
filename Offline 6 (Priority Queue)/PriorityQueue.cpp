#include<iostream>
using namespace std;

#define INFINTITY 999999; 

template<class T>
class PriorityQueue{

	T *arr;
	int size, length;

	void MaxHeapify(int i){
		int l = lchild(i);
		int r = rchild(i);

		int largest = i;

		if(l<length && arr[l]>arr[largest])
			largest = l;
		else 
			largest = i;
		
		if(r<length && arr[r]>arr[largest])
			largest = r;

		if(largest != i){
			swap(arr[i],arr[largest]);
			MaxHeapify(largest);
		}
	}

	void BuildMaxHeap(){
		for(int i = length/2 - 1; i>=0 ; i--){
			MaxHeapify(i);
		}
	}

	int parent(int i){return (i-1)/2;}
	int lchild(int i){return 2*i + 1;}
	int rchild(int i){return 2*i + 2;}

	void resize(){

	}


public:
	PriorityQueue(int size){
		arr = new T[size];
		this->size = size;
		this->length = 0;
	}

	void Insert(T &elem){
	//Inserts an element into the priority queue 
	//according to the priority of its key.
	//Time complexity: 𝑂(log𝑛).
		arr[length++] = -INFINTITY;
		
		IncreaseKey(length-1,elem); 
	}

	T FindMax(){
	//Returns the element with largest key 
	//but does not remove it. Time complexity: 𝑂(1).

		return arr[0];

	}
	T ExtractMax(){
	//Returns the element with largest key 
	//and delete the element from the heap. Time complexity: 𝑂(log𝑛).

		if (this->length <= 0 ){
			cout<<endl<<"Heap Underflow"<<endl;
			return -INFINTITY;
		}

		T max = arr[0];
		arr[0] = arr[length-1];
		length--;

		MaxHeapify(0);

		return max;
	}

	void IncreaseKey(int i,T &newKey){
	//Increase the key of the ith element to 𝑛𝑒𝑤𝐾𝑒𝑦, 
	//and relocate it to maintain heap property. Time complexity: 𝑂(log𝑛).

		if (newKey < arr[i]){
			cout<<"New key is smaller than current key"<<endl;
			return;
		}
		arr[i] = newKey;

		while (i>0 && arr[parent(i)] < arr[i]){
			swap(arr[i],arr[parent(i)]);
			i = parent(i);
		}
	} 

	void DecreaseKey(int i,T newKey){
	//Decrease the key of the ith element to 𝑛𝑒𝑤𝐾𝑒𝑦, 
	//and relocate it to maintain heap property. Time complexity: 𝑂(log𝑛).

	if (newKey > arr[i]){
			cout<<"New key is larger than current key"<<endl;
			return;
		}

		arr[i] = newKey;

		MaxHeapify(i);
	}

	void Print(){
	//Print the heap. Time complexity: 𝑂(𝑛).

		cout<<"Capacity: "<<this->size<<endl<<"Current length: "<<this->length<<endl;
		cout<<"Elements: ";
		for(int i = 0 ; i<length; i++){
			cout<<arr[i]<<" ";
		}
		cout<<endl;
	}

	~PriorityQueue(){
		delete arr;
		length = 0;
		size = 0;
	}


};



int main(){
	int ch;
	PriorityQueue<int> pq(100);

	bool quit = false;
	while(!quit){
		cout<<"1. Insert"<<endl;
		cout<<"2. FindMax"<<endl;
		cout<<"3. ExtractMax"<<endl;
		cout<<"4. IncreaseKey"<<endl;
		cout<<"5. DecreaseKey"<<endl;
		cout<<"6. Print"<<endl;
		cout<<"7. Exit"<<endl<<endl;

		cout<<"Enter your choice: ";

		cin>>ch;
		switch(ch){
			case 1:
				cout<<"Enter your element: ";
				int num;
				cin>>num;
				pq.Insert(num);
				break;
			case 2:
				cout<<"Max element: "<<pq.FindMax()<<endl;
				break;
			case 3:
				cout<<"Max extracted: "<<pq.ExtractMax()<<endl;\
				break;
			case 4:
				cout<<"Enter the index & new key: ";
				int index, newKey;
				cin>>index>>newKey;
				pq.IncreaseKey(index,newKey);
				break;
			case 5:
				cout<<"Enter the index & new key: ";
				cin>>index>>newKey;
				pq.DecreaseKey(index,newKey);
				break;	
			case 6:
				pq.Print();
				break;
			case 7:
				quit = true;
				break;
		}	
	}

	return 0;
	
}