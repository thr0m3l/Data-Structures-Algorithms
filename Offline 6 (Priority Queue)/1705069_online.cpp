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

		arr[length++] = -INFINTITY;

		IncreaseKey(length-1,elem);
	}

	T FindMax(){


		return arr[0];

	}
	T ExtractMax(){


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

	if (newKey > arr[i]){
			cout<<"New key is larger than current key"<<endl;
			return;
		}

		arr[i] = newKey;

		MaxHeapify(i);
	}

	void Print(){


		cout<<"Capacity: "<<this->size<<endl<<"Current length: "<<this->length<<endl;
		cout<<"Elements: ";
		for(int i = 0 ; i<length; i++){
			cout<<arr[i]<<" ";
		}
		cout<<endl;
	}

	int count (T val, int i = 0){

        if (arr[i] <= val && i < length)
            return 0;
        else if (i >= length/2)
            return 1;
        else
            return 1 + count(val,lchild(i)) + count (val, rchild(i));



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
		cout<<"7. Number of elements larger"<<endl;
		cout<<"8. Exit"<<endl<<endl;

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
			case 8:
				quit = true;
				break;
            case 7:
                int number;
                cout<<"Enter a number: ";
                cin>>number;
                cout<<"Number of elements larger: "<<pq.count(number)<<endl;;
                break;
		}
	}

	return 0;

}

//1 12 1 6 1 7 1 3 1 5 1 4 1 3 1 2 1 1 1 0 1 -1
