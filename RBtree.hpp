#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>

template<class Key, class Value, class Compare>
class RBtree
{
	private:

		static const bool BLACK = false;
		static const bool RED = true;
		
		class Node
		{
			private:
			protected:
			public:
			Node();
			Node(Key,Value);
			Key k;
			Value v;
			bool color;

			Node* parrent;
			Node* left;
			Node* right;
		};

	Node* root;
	Node* sentinel;
	void RBfix(Node*);
	void rsh(Node*); //Rekurencyjny SHow
	void lr(Node*);  //lewa rotacja
	void rr(Node*);  //prawa rotacja
	protected:
	public:
		RBtree();
		void add(Key,Value);
		void show();
};

template<class Key, class Value, class Compare>
RBtree<Key,Value,Compare>::Node::Node()
{
	color = BLACK;
	parrent = nullptr;
	left = nullptr;
	right = nullptr;
}

template<class Key, class Value, class Compare>
RBtree<Key,Value,Compare>::RBtree()
{
	sentinel = new Node();
	root = sentinel;
}


template<class Key, class Value, class Compare>
RBtree<Key,Value,Compare>::Node::Node(Key kee,Value val)
{
	k = kee;
	v = val;
	color = BLACK;
	parrent = nullptr;
	left = nullptr;
	right = nullptr;
}//void RBtree<Key,Value,Compare>::Node::Node(Key k,Value v)


template<class Key, class Value, class Compare>
void RBtree<Key,Value,Compare>::add(Key k,Value v)
{
	Compare comp; //obiekt porównujący
	Node* newone;
	newone = new Node(k,v); //z
	Node* y; //y
	Node* x; //x
	y = sentinel;
	x = root;
	while (x != sentinel)
	{
		y = x;
		if ( comp.less(newone->k,x->k) )
			x = x->left;
		else
			x = x->right;
	}
	newone->parrent = y;
	if (y == sentinel)
		root = newone;
	else
		if ( comp.less(newone->k,y->k) )
			y->left = newone;
		else
			y->right = newone;
	newone->left = sentinel;
	newone->right = sentinel;
	newone->color = RED;
	this -> show();
	RBfix(newone);
}

template<class Key, class Value, class Compare>
void RBtree<Key,Value,Compare>::lr(Node* x)
{
	Node* y;
	y = x->right;
	x->right = y->left;
	if (y->left != sentinel)
		y->left->parrent = x;
	y->parrent = x->parrent;
	if (x->parrent == sentinel)
		root = y;
	else
		if (x == x->parrent->left)
			x->parrent->left = y;
		else
			x->parrent->right = y;
	y->left = x;
	x->parrent = y;
	
}

template<class Key, class Value, class Compare>
void RBtree<Key,Value,Compare>::rr(Node* x)
{
	Node* y;
	y = x->left;
	x->left = y->right;
	if (y->right != sentinel)
		y->right->parrent = x;
	y->parrent = x->parrent;
	if (x->parrent == sentinel)
		root = y;
	else
		if (x == x->parrent->right)
			x->parrent->right = y;
		else
			x->parrent->left = y;
	y->right = x;
	x->parrent = y;
	
}

template<class Key, class Value, class Compare>
void RBtree<Key,Value,Compare>::RBfix(Node* z)
{
	Node* y;
	while (z->parrent->color == RED && z != root)
	{
		if (z->parrent ==  z->parrent->parrent->left)
		{
			y = z->parrent->parrent->right;
			if (y->color == RED)
			{
				z->parrent->color = BLACK;
				y->color = BLACK;
				z->parrent->parrent->color = RED;
				z = z->parrent->parrent;
			}
			else
			{
				if(z == z->parrent->right)
				{
					z = z->parrent;
					this->lr(z);
				}
				z->parrent->color = BLACK;
				z->parrent->parrent->color = RED;
				this->rr(z->parrent->parrent);

			}
		}
		else
		{	
			y = z->parrent->parrent->left;
			if (y->color == RED)
			{
				z->parrent->color = BLACK;
				y->color = BLACK;
				z->parrent->parrent->color = RED;
				z = z->parrent->parrent;
			}
			else
			{
				if(z == z->parrent->left)
				{
					z = z->parrent;
					this->rr(z);
				}
				z->parrent->color = BLACK;
				z->parrent->parrent->color = RED;
				this->lr(z->parrent->parrent);

			}
		}
	}
	root->color = BLACK;
}

template<class Key, class Value, class Compare>
void RBtree<Key,Value,Compare>::rsh(Node* start)
{
	if (start != nullptr)
	{
		std::cout << start->k << start->v << start->color << std::endl;
		this->rsh(start->left);
		this->rsh(start->right);
	}

}

template<class Key, class Value, class Compare>
void RBtree<Key,Value,Compare>::show()
{
	this->rsh(root);
}















#endif