#include<iostream>
#define MAXSIZE 10
using namespace std;

template <class T>
class Stack
{
    T *st;
    int tos, size;

public:
    Stack(){
        st = new T[MAXSIZE];
        tos = 0;
        size = MAXSIZE;
    }

    Stack(const Stack<T> &a){
        tos = 0;
        size = a.size;
        st = new T[size];
        for(int i=0; i<a.tos; i++)
        {
            st[i] = a.st[i];
            tos++;
        }
    }
    void push(T obj){
        if (tos == size)
            resize(size+=10);

        st[tos++] = obj;
    }
    void push(T *arr,int size){
        for(int i=0; i<size; i++)
        {
            this->push(arr[i]);
        }
    }
    void push(Stack<T> temp){
        while(!temp.isEmpty())
        {
            this->push(temp.pop());
        }
    }
    
    int sizeofStack(){return tos;}
    T& top(){return st[tos-1];}
    int maxSize(){return size;}
    bool isEmpty(){return !tos;}

    
    T pop(){
        if(size - tos >= 10) resize(size-=10);
        return tos != 0 ? st[--tos] : -2147483647;
    }
    void resize(int size){
        T *tempStack = new T[size];
        for(int i = 0; i < tos; i++)
        {
            tempStack[i] = st[i];
        }
        delete[] st ;
        st = tempStack;
    }
    template<class S>
    friend ostream &operator<<(ostream &stream, Stack<S> const &st);

    void menu(){
        cout<<"1. Push an Element"<<endl;
        cout<<"2. Push an Array"<<endl;
        cout<<"3. Pop"<<endl;
        cout<<"4. Top"<<endl;
        cout<<"5. Size"<<endl;
        cout<<"6. Show all elements of stack"<<endl; 
        cout<<"7. Exit"<<endl;
        cout<<"Enter Your Choice:"<<endl<<endl;
    }
    ~Stack(){
        delete[] st;
    }

};

//Custom Inserter
template<class S>
ostream &operator<<(ostream &stream, Stack<S> const &st){
    for(int i=0;i<st.tos;i++){
        stream<<st.st[i]<<" ";
    }
    stream<<endl; 
    return stream;
}


int main(){
    Stack<int> st;
    bool exit = 0;
    int choice;
    while(!exit)
    {
        st.menu();
        cin>>choice;
        if(choice == 1)
        {
            int x;
            cout<<"Enter the number you want to push: ";
            cin>>x;
            st.push(x);
        }
        else if(choice == 2)
        {
            cout<<"Enter the elements you want to push preceded by number of elements: ";
            int size;
            cin>>size;
            int arr[size];
            for(int i=0; i<size; i++)
            {
                cin>>arr[i];
            }
            st.push(arr, size);
        }
        else if(choice == 3)
        {
            cout<<"Popped Number: "<<st.pop()<<endl<<endl;
        }
        else if(choice == 4)
        {
            cout<<"The Element at the top: "<<st.top()<<endl<<endl;
        }
        else if(choice == 5)
        {
            cout<<"Current size of the stack: "<<st.sizeofStack()<<endl<<endl;
            cout<<"Max Size of the stack: "<<st.maxSize()<<endl<<endl;
        }
        else if(choice == 7)
        {
            exit = true;
          
        } else if (choice == 6){
            cout<<"Elements of the stack: "<<st<<endl;  
        }

    }
}