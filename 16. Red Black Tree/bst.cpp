#include<iostream>
using namespace std;

class RBTree{
	
	class Node{

		public:
		int key;
		bool color;
		Node *left, *right, *p;

		Node(int item){
			key = item;
			left = right = NULL;
		}
	};

private:
	Node *root;

	Node* search(int key, Node *root){
		Node *n = root;
		while(n != NULL){
			if(n->key == key )
				return n;
			else if (key > n->key)
				n = n->right;
			else if (key < n->key)
				n = n->left;
		}
		return NULL;
	}


	// Node* parent(Node *x){
	// 	Node *n = root;
	// 	Node *temp;
	// 	while(n != NULL){
	// 		if(n == x)
	// 			return temp;
	// 		else if (x->key > n->key){
	// 			temp = n;
	// 			n = n->right;
	// 		} else if (x->key < n->key){
	// 			temp = n;
	// 			n = n->left;
	// 		}
	// 	}
	// 	return NULL;
	// }

	Node* successor(int x){
		Node *n = search(x,root);

		if(n->right != NULL)
			return min(n->right);
		Node *y = parent(n);

		while(y != NULL && n == y->right){
			n = y;
			y = parent(y);
		}
		return y;

	}

	void transplant(Node *u, Node *v){

		Node *p1 = u->p;
		Node *p2 = v->p;
		if (p1 != NULL)
			root = v;
		else if (v == p2->left )
			p1->left = v;
		else 
			p2->right = v;

		if(v != NULL)
			p2 = p1;

	}

	Node* max(Node *n){
		while(n->right != NULL){
			n = n->right;
		}

		return n;
	}

	Node* min(Node *n){
		while(n->left != NULL){
			n = n->left;
		}

		return n;
	}

	Node* Delete(int x, Node* t){
        Node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->key)
            t->left = Delete(x, t->left);
        else if(x > t->key)
            t->right = Delete(x, t->right);
        else if(t->left && t->right)
        {
            temp = min(t->right);
            t->key = temp->key;
            t->right = Delete(t->key, t->right);
        }
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

public:
	RBTree(){
		root = NULL;
	}

	bool search(int key){
		Node *n = this->root;
		while(n != NULL){
			if(n->key == key )
				return true;
			else if (key > n->key)
				n = n->right;
			else if (key < n->key)
				n = n->left;
		}
		return false;
	}

	

	void insert(int key){
		Node *y = NULL;
		Node *x = this->root;

		while(x!= NULL){
			y = x;
			if(key < x->key)
				x = x->left;
			else if (key > x->key)
				x = x->right;
			else 
				return;
		}

		x = new Node(key);

		if(y == NULL)
			this->root = x;
		else if ( x->key < y->key )
			y->left = x;
		else
			y->right = x;
	}

	void Delete (int key){
		root = Delete(key, root);
	}

	void inorder(){
		inorderRec(root);
	}
	void preorder(){
		preorderRec(root);
	}

	void inorder2(){
		Node *minm = min(root);
		
		while(minm != NULL){
			cout<<minm->key<<" ";
			minm = successor(minm->key);
		}
	}

};

int main(){
	
}