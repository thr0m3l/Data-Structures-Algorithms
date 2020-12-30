#include<iostream>
using namespace std;
#define RED 1
#define BLACK 0
#define INF INT32_MIN

class RBTree{
	
	class Node{
		public:
		int key, color;
		Node *left, *right, *p;

		Node(int item){
			key = item;
		 	p = left = right = NULL;
			color = RED;
		}
	};

private:
	Node *root, *nil;

	Node* min(Node *n){
		while(n->left != nil){
			n = n->left;
		}
		return n;
	}

	Node* successor(Node *n){
		if (n->right != nil) return min(n->right);
		Node *x = n->p;
		while(x != nil && n == x->right){
			n = x;
			x = x->p;
		}
		return x;
	}

	void left_rotate(Node *x){
		Node *y = x->right;
		x->right = y->left;
		if(y->left != nil) y->left->p = x;
		y->p = x->p;
		if (x->p == nil) root = y; //if x is the root
		else if (x->p->left == x) x->p->left = y; //if x is left child
		else x->p->right = y; //if x is right child
		y->left = x;
		x->p = y;
		
	}

	void right_rotate(Node *x){
		Node *y = x->left;
		x->left = y->right;
		y->p = x->p;
		if(y->right != nil) y->right->p = x;
		if (x->p == nil) root = y; //if x is the root
		else if (x->p->left == x) x->p->left = y; //if x is left child
		else x->p->right = y; //if x is right child
		y->right = x;
		x->p = y;
		
	}

	Node* find(int k){
		Node *x = root;
		while(x != nil){
			if (k == x->key) return x;
			else if (k > x->key) x = x->right;
			else x = x->left;
		}
		return x;
	}
public:
	
	RBTree(){

		nil = new Node(INF);
		root = nil;
		nil->left = nil;
		nil->right = nil;
		nil->p = nil;
		nil->color = BLACK;
		nil->key = INF;
	}

	bool search(int k){
		Node *x = find(k);
		if (x != nil && x->key == k) return true;
		else return false;
	}
	
	void insert(int k){
		Node *x = root, *y = nil;
		while(x != nil){
			//Finds the insertion position of new node
			y = x;
			if (k > x->key) x = x->right;
			else x = x->left;	
		}
		
		x = new Node(k);
		x->p = y;
		x->left = nil;
		x->right = nil;
		x->color = RED;
		
		if (y == nil) root = x; //Tree Empty
		else if (x->key > y->key) y->right = x; //New node is right child
		else if (x->key < y->key) y->left = x; //New node is left child
		
		insert_fixup(x);
	}

	void insert_fixup(Node *z){
		
		root->color = BLACK;
		if (z == root || z->p->color == BLACK) return;
		
		//Case 1-3: z->p is a left child
		else if  (z->p->p->left == z->p){
			
			Node *y = z->p->p->right; //uncle of z

			if(y->color == RED){
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				insert_fixup(z->p->p);
			} 
			//Case 2: z's uncle is black & z is right child
			else {
				if (z == z->p->right){
					//make z a left child
					z = z->p;
					left_rotate(z);
				}
				//recolor and rotate
				//Case 3 : z's uncle is black & z is left child
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_rotate(z->p->p);
			}

		}
		//Case 4-6: z->p is a right child 
		else if (z->p->p->right == z->p){
			Node *y = z->p->p->left; //uncle

			//Case 4
			if (y->color == RED){
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				insert_fixup(z->p->p);
			}
			else {
				//Case 5
				if (z == z->p->left){
					//make z a right child
					z = z->p;
					right_rotate(z);
				}
				//recolor and rotate
				//Case 6 : z's uncle is black & z is right child
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_rotate(z->p->p);
			}
		}
		

	}

	void delete_(int k){
		Node *z = find(k), *y, *x = NULL;
		if (z == nil) return;
		
		if (z->left == nil || z->right == nil) y = z;
		else y = successor(z);

		if (y->left != nil) x = y->left;
		else x = y->right;
		
		x->p = y->p;
		if (y->p == nil) root = x;
		else if (y == y->p->left) y->p->left = x;
		else y->p->right = x;

		if (y != z) z->key = y->key;
		
		if (y->color == BLACK) delete_fixup(x);

		delete y;
	}


	void delete_fixup(Node *x){
		
		while( x != root && x->color == BLACK){
			if (x == x->p->left){
				Node *w = x->p->right;
				//Case 1: sibling is RED
				if (w->color == RED){
					w->color == BLACK;
					x->p->color = RED;
					left_rotate(x->p);
					w = x->p->right;
				}
				//Case 2: sibling is black && both children are black
				if (w->left->color == BLACK && w->right->color == BLACK) {
                	w->color = RED;
                	x = x->p;
            	} 
				else {
                	//Case 3: sibling's left child is red & right child is black
					if (w->right->color == BLACK) {
                    	w->left->color = BLACK;
                    	w->color = RED;
                    	right_rotate(w);
                    	w = x->p->right;
                	}
					//Case 4: sibling's right child is red & left child is black
                	w->color = x->p->color;
                	x->p->color = BLACK;
                	w->right->color = BLACK;
                	left_rotate (x->p);
                	x = root;
				}
			} 
			else {
				Node *w = x->p->left;

				if (w->color == RED){
					w->color == BLACK;
					x->p->color = RED;
					right_rotate(x->p);
					w = x->p->left;
				}

				if (w->left->color == BLACK && w->right->color == BLACK) {
                	w->color = RED;
                	x = x->p;
            	} 
				else {
                	if (w->left->color == BLACK) {
                    	w->right->color = BLACK;
                    	w->color = RED;
                    	left_rotate(w);
                    	w = x->p->left;
                	}
                	w->color = x->p->color;
                	x->p->color = BLACK;
                	w->left->color = BLACK;
                	right_rotate (x->p);
                	x = root;
				}
			}
		}
		x->color = BLACK;
	}
	void print(Node *n){
		if (n != nil){
			cout<<n->key;
			if(n->color == BLACK) cout<<":b";
			else cout<<":r";
			if (n->left != nil || n->right != nil){
				cout<<"(";
				print(n->left);
				cout<<")(";
				print(n->right);
				cout<<")";
			}
		}
	}

	void parse(char c, int k){
		if (c == 'F'){
			if (!search(k)) cout<<"False";
			else cout<<"True";
		} else if (c == 'I'){
			insert(k);
			print(root);
		} else if (c == 'D'){
			delete_(k);
			print(root);
		}
		cout<<endl;
	}

};

int main(){
	RBTree rbt;
	// FILE *fp = freopen("output.txt", "w", stdout);
    // FILE *fp1 = freopen("input2.txt", "r", stdin);

	char ch = 'A';
	int k;

	while(ch != '0'){
		cin>>ch>>k;
		rbt.parse(ch, k);
		
	}

}