#include<iostream>
#include <sstream>
#include <string> 
#include<queue>

using namespace std;

class BinomialHeap{
    
    class Node
    {
        public:
        int data, deg, level;
        Node *p, *sibling, *child;

        Node(int data, int deg = 0){
            this->data = data;
            this->deg = deg;
            p = NULL;
            child = NULL;
            sibling = NULL;
            level = 0;
        }
    };

    Node *head, *tail;
    public:

    BinomialHeap(){
        head = NULL;
        tail = NULL;
    }

    void Link (Node *y, Node *z){
        //Links two binomial tree with same degree

        y->p = z;
        y->sibling = z->child;
        z->child = y;
        z->deg++;

        // cout<<"Linked "<<y->data<<" with "<<z->data<<endl;
    }

    Node* FindMin(){
        Node *y = NULL, *x = head;
        int min = INT32_MAX;

        while(x != NULL){
            if (x->data < min){
                min = x->data;
                y = x;
            }
            x = x->sibling;
        }

        return y;
    }

    Node* Merge(Node *H1, Node *H2){
        Node *H = NULL;

        if (H1 || H2){
            if (H1 && !H2){
                H = H1;
            } else if (!H1 && H2){
                H = H2;
            } else {
                Node *temp, *next, *prev, *cur;

                if (H1->deg > H2->deg){
                    H = H2;
                    next = H1;
                } else {
                    H = H1;
                    next = H2;
                }
                cur = H;

                //Reassigning siblings

                while(cur && next && cur != next){
                    if (cur->deg <= next->deg){
                        if (cur->sibling){
                            temp = cur->sibling;
                            cur->sibling = next;
                            prev = cur;
                            cur = next;
                            next = temp;
                        } else {
                            cur->sibling = next;
                            cur = next; //breaks the loop
                        }
                    } else {
                        if (prev){
                            prev->sibling = next;
                        } else {
                            H = next;
                        }
                        temp = next->sibling;
                        next->sibling = cur;
                        prev = next;
                        next = temp;
                    }
                }
            }

        }
        return H;
    }

    void Union(Node *H1, Node *H2){
        Node *H = Merge(H1, H2);

        if (H == NULL) return;

        Node *prev = NULL, *x = H, *next = x->sibling;

        while(next != NULL){
            if ((x->deg != next->deg) || 
            (next->sibling != NULL && next->sibling->deg == x->deg)){
                prev = x;
                x = next;
            } else {
                if (x->data <= next->data) {
                    x->sibling = next->sibling;
                    Link(next, x);
                } else {
                    if (prev == NULL) H = next;
                    else prev->sibling = next;
                    Link(x, next);
                    x = next;          
                }
            }
            next = x->sibling;
        }

        head = H;

    }

    void Union(BinomialHeap bh1){
        // if (this->head != NULL) cout<<"Union "<<this->head->data<<"--"<<bh1.head->data<<"\n";
        
        if (this->head != NULL && this->head->deg > bh1.head->deg) Union(this->head, bh1.head);
        else Union(bh1.head, this->head);
    }

    Node* ExtractMin(){
        tail = NULL;

        Node *x = head, *min_node = head, *t = NULL;
        int min = head->data;

        while(x->sibling != NULL){
            if (x->sibling->data < min){
                min = x->sibling->data;
                min_node = x->sibling;
                t = x;
            }
            x = x->sibling;
        }

        if (t == NULL && min_node->sibling == NULL){
            head = NULL;
        } else if (t == NULL){
            head = min_node->sibling;
        } else if (t->sibling == NULL){
            t = NULL;
        } else {
            t->sibling = min_node->sibling;
        }

        if(min_node->child != NULL){
            reverse(min_node->child);
            min_node->child->sibling = NULL;
        }

        Union(head, tail);
        return min_node;
    }

    void reverse(Node *x){
        if ( x->sibling != NULL){
            reverse(x->sibling);
            x->sibling->sibling = x;
        } else {
            tail = x;
        }
    }

    void Insert(int key){
        Node *x = new Node(key, 0);
        Union(head, x);
    }

    void print(){
        Node *H = head, *c = NULL;
        cout<<"Printing Binomial Heap. . .\n";

        while(H != NULL){
            Node *prev = NULL;

            cout<<"Binomial Tree, B"<<H->deg<<"\n";
            cout<<"Level 0 : "<<H->data<<endl;
            
            queue<Node*> q;

            c = H->child;
            if (c != NULL) q.push(c);
            H->level = 0; //level

            while(!q.empty()){
                int level = 1;
                Node *itr = q.front();
                q.pop();

                while(itr != NULL){
                    itr->level = itr->p->level + 1; //level

                    if (prev == NULL){
                        cout<<"Level 1 : ";
                    } else if (prev->level < itr->level){
                        cout<<"\nLevel "<<itr->level<<" : ";
                    }

                    cout<<itr->data<<" ";

                    prev = itr; //tracks which node was printed

                    if (itr->child != NULL) q.push(itr->child);
                    
                    itr = itr->sibling;
                }
            }
            cout<<"\n";
            H = H->sibling;
        }
    }

};

int main(){
    // FILE *fp = freopen("output.txt", "w", stdout);
    // FILE *fp1 = freopen("input.txt", "r", stdin);
    
    BinomialHeap bh;

    char ch = 'I';
    int num = 0;

    while(cin>>ch){
        // cin>>ch;
        if (ch == 'I'){
            cin>>num;
            bh.Insert(num);
        } else if (ch == 'P'){
            bh.print();
        } else if (ch == 'F'){
            int ans = bh.FindMin()!= NULL ? bh.FindMin()->data : -1;
            cout<<"Find-Min returned "<<ans<<endl;
        } else if (ch == 'E'){
            cout<<"Extract-Min returned "<<bh.ExtractMin()->data<<endl;
        } else if (ch == 'U'){
            string line;
            getline(cin,line);
            istringstream is(line);
            int n;
            BinomialHeap bh1;
            while( is >> n ) {
                bh1.Insert(n);
                
            }
            bh.Union(bh1);
        }
    }

}