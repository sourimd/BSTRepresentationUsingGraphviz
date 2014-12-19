#include <iostream>
#include <fstream>

class Node{
private:
	Node *left;
	int value;
	Node *right;
public:
	void setValue(int v){ value = v; }
	void setLeft(Node * n){ left = n; }
	void setRight(Node * n){ right = n; }
	Node * getLeft(){ return left; }
	int getValue(){ return value; }
	Node * getRight(){ return right; }
	Node(int v):value(v), left(NULL),right(NULL){}
	Node():value(0), left(NULL),right(NULL){}
	~Node(){ delete left; delete right;}
};

void insert(Node ** rt, int v){
	Node * newNode = new Node(v);
	if(*rt == NULL){
		*rt = newNode;
	}
	else{
		if( v < (*rt)->getValue() ){
			if( (*rt)->getLeft() == NULL ){
				(*rt)->setLeft(newNode);
			}
			else{
				Node * lc = (*rt)->getLeft();
				insert(&lc, v);
			}
		}
		else{
			if( (*rt)->getRight() == NULL ){
				(*rt)->setRight(newNode);
			}
			else{
				Node * rc = (*rt)->getRight();
				insert(&rc, v);
			}
		}
	}
}

void print(std::fstream & op, Node ** rt){
	op << "\""<< (*rt)->getValue() << "\"[label=\"<f0>left|<f1>"<<(*rt)->getValue()<<"|<f2>right\",shape=Mrecord]" << std::endl;
	if( (*rt)->getLeft() ){
		op << "\"" << (*rt)->getValue() << "\":f0->\"" << (*rt)->getLeft()->getValue() << "\"" << std::endl;
		Node * lc;
		lc = (*rt)->getLeft();
		print(op, &lc);
	}
	if( (*rt)->getRight() ){
		op << "\"" << (*rt)->getValue() << "\":f2->\"" << (*rt)->getRight()->getValue() << "\"" << std::endl;
		Node * rc;
		rc = (*rt)->getRight();
		print(op, &rc);
	}
}

int main(){
	Node * root;
	root = NULL;

	insert(&root, 15);
	insert(&root, 20);
	insert(&root, 5);
	insert(&root, 51);
	insert(&root, 54);
	insert(&root, 17);
	insert(&root, 12);
	insert(&root, 34);
	insert(&root, 45);
	insert(&root, 1);
	std::fstream output;
	output.open("tree.gv", std::ios::out);
	output << "digraph G{" << std::endl;
	print(output, &root);
	output << "}" << std::endl;
	output.close();
	
}