#include<iostream>
#define MAXSIZE 10
using namespace std;

template <class T>
class Queue
{
    T *q;
    int head, tail, size;

public:
    Queue(){
        q = new T[MAXSIZE];
        head = 0;
        tail = 0;
        size = MAXSIZE;
    }

    Queue(const Queue<T> &a){
        head = a.head;
        tail = a.tail;
        size = a.size;
        q = new T[size];
        for(int i=a.head; i<a.tail; i++)
            q[i] = a.q[i];
    }
    void enqueue(T obj){
        if(size == tail)
            resize(size+=10);
        q[tail++] = obj;
    }
    void enqueue(T *arr, int size){
        for(int i=0; i<size; i++)
        {
            this->enqueue(arr[i]);
        }
    }

    T dequeue(){
        // if(size - (tail - head) >= 10) 
        //     resize(size-=10);
        return q[head++];
    }

    int sizeofQueue(){return tail - head;}
    T& top(){return q[head];}
    int maxSize(){return size;}
    bool isEmpty(){return !tail;}

    
    void resize(int size){
        T *tempQueue = new T[size];
        for(int i = head; i < tail; i++)
        {
            tempQueue[i] = q[i];
        }
        delete[] q ;
        q = tempQueue;
    }
    template<class S>
    friend ostream &operator<<(ostream &stream, Queue<S> const &st);

    void menu(){
        cout<<"1. Enqueue"<<endl;
        cout<<"2. Enqueue an Array"<<endl;
        cout<<"3. Dequeue"<<endl;
        cout<<"4. Front"<<endl;
        cout<<"5. Rear"<<endl;
        cout<<"6. Size"<<endl;
        cout<<"7. Show all elements of queue"<<endl; 
        cout<<"8. Exit"<<endl;
        cout<<"Enter Your Choice:"<<endl<<endl;
    }

    T& front(){ return q[head];}
    T& rear (){ return q[tail-1];}
    ~Queue(){ delete[] q;}

};

//Custom Inserter
template<class S>
ostream &operator<<(ostream &stream, Queue<S> const &st){
    for(int i=st.head;i<st.tail;i++){
        stream<<st.q[i]<<" ";
    }
    stream<<endl; 
    return stream;
}

int main(){
    Queue<int> q;
    bool exit = 0;
    int choice;
    while(!exit)
    {
        q.menu();
        cin>>choice;
        if(choice == 1)
        {
            int x;
            cout<<"Enter the number you want to enqueue: ";
            cin>>x;
            q.enqueue(x);
        }
        else if(choice == 2)
        {
            cout<<"Enter the elements you want to enqueue preceded by number of elements: ";
            int size;
            cin>>size;
            int arr[size];
            for(int i=0; i<size; i++)
            {
                cin>>arr[i];
            }
            q.enqueue(arr, size);
        }
        else if(choice == 3)
        {
            cout<<"Dequeued element: "<<q.dequeue()<<endl<<endl;
        }
        else if(choice == 4)
        {
            cout<<"The Element at the front: "<<q.front()<<endl<<endl;
        }
        else if(choice == 6)
        {
            cout<<"Current size of the queue: "<<q.sizeofQueue()<<endl<<endl;
            cout<<"Max Size of the queue: "<<q.maxSize()<<endl<<endl;
        }
        else if(choice == 5){
            cout<<"The Element at the rear: "<<q.rear()<<endl<<endl;
        }
        else if(choice == 8)
        {
            exit = true;
          
        } else if (choice == 7){
            cout<<"Elements of the queue: "<<q<<endl;  
        }

    }
}