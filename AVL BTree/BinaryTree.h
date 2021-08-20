
/*****************************************
* Author: Emmett Hale
*
* Purpose: Unbalanced Binary Search Tree
*
* Date Created: 6/2/2021
*****************************************/
#pragma once
#include <queue>
using std::queue;

template <typename T> 
class TreeNode;

/*****************************************
* Class: Binary Tree
* 
* Purpose: Binary Search Tree
* 
* Will be base for AVL tree
*****************************************/
template <typename T>
class BinaryTree
{
	
public:
	
	BinaryTree();
	BinaryTree(T data);
	BinaryTree(const BinaryTree& copy);
	BinaryTree& operator=(const BinaryTree& rhs);
	~BinaryTree();

	void ClearTree();

	int GetHeight();

	virtual void AddNode(const T& Data);
	virtual void RemoveNode(const T& Data);

	void DepthTraverse(void(*visit)(const T&));
	void BreadthTraverse(void(*visit)(const T&));

protected:
	void SubDepthTraverse(void(*visit)(const T&), TreeNode<T> * node);
	TreeNode<T>* MakeNode(T data);
	TreeNode<T>* MakeNode();
	TreeNode<T> * m_root;
};

/*****************************************
* Class: Tree Node
*
* Purpose: Node class for binary trees
*****************************************/
template <typename T>
class TreeNode
{
	friend class BinaryTree<T>;
public:
	T m_data;
	TreeNode<T>* m_left_node;
	TreeNode<T>* m_right_node;
	int m_weight; //LLH, LH, E, RH, RRH
	~TreeNode();
private:
	TreeNode();
	TreeNode(T data);
	TreeNode(const TreeNode& copy);
	TreeNode<T>& operator=(const TreeNode& rhs);
	void ClearNode(TreeNode<T>* node);
	int CalcHeight(TreeNode<T>* node);
	
};

/*****************************************
* Default Ctor
*****************************************/
template <typename T>
TreeNode<T>::TreeNode() : m_left_node(nullptr), m_right_node(nullptr), m_weight(0)
{	}

/*****************************************
* One Arg Ctor
*****************************************/
template <typename T>
TreeNode<T>::TreeNode(T data) : m_left_node(nullptr), m_right_node(nullptr), m_data(data), m_weight(0)
{	}

/*****************************************
* Copy Ctor
*****************************************/
template <typename T>
TreeNode<T>::TreeNode(const TreeNode& copy) : m_left_node(nullptr), m_right_node(nullptr), m_data(copy.m_data), m_weight(copy.m_weight)
{
	if (copy.m_left_node != nullptr)
	{
		m_left_node = new TreeNode<T>();
		*m_left_node = *copy.m_left_node;
	}

	if (copy.m_right_node != nullptr)
	{
		m_right_node = new TreeNode<T>();
		*m_right_node = *copy.m_right_node;
	}
}

/*****************************************
* Assignment Operator
*****************************************/
template <typename T>
TreeNode<T>& TreeNode<T>::operator=(const TreeNode<T>& rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_weight = rhs.m_weight;
		ClearNode(this);

		if (rhs.m_left_node)
		{
			m_left_node = new TreeNode();
			*m_left_node = *rhs.m_left_node;
		}

		if (rhs.m_right_node)
		{
			m_right_node = new TreeNode();
			*m_right_node = *rhs.m_right_node;
		}
	}

	return *this;
}

/*****************************************
* Dtor
*****************************************/
template <typename T>
TreeNode<T>::~TreeNode()
{
	ClearNode(this);
}

/*****************************************
* Calculates the height of a node
*****************************************/
template <typename T>
int TreeNode<T>::CalcHeight(TreeNode<T>* node)
{
	int height = 1;
	int left = 0;
	int right = 0;

	if (node->m_left_node != nullptr)
	{
		left = CalcHeight(node->m_left_node);
	}

	if (node->m_right_node != nullptr)
	{
		right = CalcHeight(node->m_right_node);
	}

	if (left > right)
	{
		height += left;
	}
	else
	{
		height += right;
	}

	return height;
}

/*****************************************
* Clears the nodes data and its subnodes
*****************************************/
template <typename T>
void TreeNode<T>::ClearNode(TreeNode<T>* node)
{
	if (node->m_right_node != nullptr)
	{
		ClearNode(node->m_right_node);
		delete node->m_right_node;
		node->m_right_node = nullptr;
	}

	if (node->m_left_node != nullptr)
	{
		ClearNode(node->m_left_node);
		delete node->m_left_node;
		node->m_left_node = nullptr;
	}
}

/*****************************************
* Default Ctor
*****************************************/
template <typename T>
BinaryTree<T>::BinaryTree() : m_root(nullptr)
{	}

/*****************************************
* One Arg Ctor
*****************************************/
template <typename T>
BinaryTree<T>::BinaryTree(T new_data) : m_root(new TreeNode<T>(new_data))
{	}

/*****************************************
* Deep Copy Ctor
*****************************************/
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& copy) : m_root(nullptr)
{	
	if (copy.m_root != nullptr)
	{
		m_root = new TreeNode<T>(*copy.m_root);
	}
}

/*****************************************
* Deep Copy op=
*
* Make sure not to pass parts of the tree
* you are copying to
*
* Make temp copies before hand
*****************************************/
template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& rhs)
{
	if (this != &rhs)
	{
		delete m_root;
		m_root = nullptr;

		if (rhs.m_root != nullptr)
		{
			m_root = new TreeNode<T>(*rhs.m_root);
		}
	}

	return *this;
}


/*****************************************
* Dtor
*****************************************/
template <typename T>
BinaryTree<T>::~BinaryTree()
{
	ClearTree();
}


/*****************************************
* Function: Empties the tree
*
* Does not clear the current tree's data
*****************************************/
template <typename T>
void BinaryTree<T>::ClearTree()
{
	if (m_root != nullptr)
	{
		m_root->ClearNode(m_root);
	}

	delete m_root;
	m_root = nullptr;
}

/*****************************************
* Get that height
*****************************************/
template <typename T>
int BinaryTree<T>::GetHeight()
{
	int to_return = 0;
	if (m_root != nullptr)
	{
		to_return = m_root->CalcHeight(m_root);
	}

	return to_return;
}


/*****************************************
* Adds a node to the binary tree in a sorted
* manner
*****************************************/
template <typename T>
void BinaryTree<T>::AddNode(const T& Data)
{
	TreeNode<T>* current = m_root;

	bool done = false;

	if (m_root == nullptr)
	{
		m_root = new TreeNode<T>(Data);
		done = true;
	}

	while (!done)
	{
		if (Data < current->m_data)//Go left
		{
			if (current->m_left_node != nullptr)
			{
				current = current->m_left_node;
			}
			else
			{
				current->m_left_node = new TreeNode<T>(Data);
				done = true;
			}
		}
		else //Go right
		{
			if (current->m_right_node != nullptr)
			{
				current = current->m_right_node;
			}
			else
			{
				current->m_right_node = new TreeNode<T>(Data);
				done = true;
			}
		}
	}
}


/*****************************************
* Removes a node from the tree
*****************************************/
template <typename T>
void BinaryTree<T>::RemoveNode(const T& Data)
{
	TreeNode<T>* current = m_root;
	TreeNode<T>* prev = nullptr;

	bool done = false;

	//If the only item in the tree is to be removed
	if (m_root->m_data == Data &&
		m_root->m_left_node == nullptr &&
		m_root->m_right_node == nullptr)
	{
		delete m_root;
		m_root = nullptr;
		done = true;
	}

	TreeNode<T>* to_replace = nullptr;

	while (current != nullptr && !done)
	{
		if (Data < current->m_data)//Go left
		{
			if (current->m_left_node != nullptr)
			{
				prev = current;
				current = current->m_left_node;

				if (current->m_data == Data &&
					current->m_left_node == nullptr &&
					current->m_right_node == nullptr)
				{
					delete current;
					prev->m_left_node = nullptr;
					done = true;
				}
			}
			else
			{
				done = true; //Not in tree
			}
		}
		else if (Data > current->m_data)//Go right
		{
			if (current->m_right_node != nullptr)
			{
				prev = current;
				current = current->m_right_node;

				if (current->m_data == Data &&
					current->m_left_node == nullptr &&
					current->m_right_node == nullptr)
				{
					delete current;
					prev->m_right_node = nullptr;
					done = true;
				}
			}
			else
			{
				done = true; //Not in tree
			}
		}
		else
		{
			//Find replacment node

			to_replace = current;

			if (current->m_left_node != nullptr) //go left
			{
				prev = current;
				current = current->m_left_node;
				bool first = true;

				while (current->m_right_node != nullptr)
				{
					prev = current;
					current = current->m_right_node;
					first = false;
				}

				to_replace->m_data = current->m_data;

				if (!first)
				{
					prev->m_right_node = current->m_left_node;
				}
				else
				{
					prev->m_left_node = current->m_left_node;
				}

				delete current;

				done = true;
			}
			else // go right
			{
				prev = current;
				current = current->m_right_node;
				bool first = true;

				while (current->m_left_node != nullptr)
				{
					prev = current;
					current = current->m_left_node;
					first = false;
				}

				to_replace->m_data = current->m_data;

				if (!first)
				{
					prev->m_left_node = current->m_right_node;
				}
				else
				{
					prev->m_right_node = current->m_right_node;
				}

				delete current;

				done = true;
			}
		}
	}
	
}

/*****************************************
* Visit each node in the tree 
*****************************************/
template <typename T>
void BinaryTree<T>::DepthTraverse(void(*visit)(const T&))
{
	SubDepthTraverse(visit, m_root);
}

/*****************************************
* Called by binary tree to traverse
*****************************************/
template <typename T>
void BinaryTree<T>::SubDepthTraverse(void(*visit)(const T &), TreeNode<T>* node)
{
	visit(node->m_data);

	if (node->m_left_node != nullptr)
	{
		SubDepthTraverse(visit, node->m_left_node);
	}

	if (node->m_right_node != nullptr)
	{
		SubDepthTraverse(visit, node->m_right_node);
	}
}

/*****************************************
* Visit each node in the tree
*****************************************/
template <typename T>
void BinaryTree<T>::BreadthTraverse(void(*visit)(const T&))
{
	queue<TreeNode<T>*> visit_queue;
	visit_queue.push(m_root);

	while (!visit_queue.empty())
	{
		TreeNode<T>* temp = visit_queue.front();
		visit_queue.pop();

		visit(temp->m_data);

		if (temp->m_left_node != nullptr)
		{
			visit_queue.push(temp->m_left_node);
		}

		if (temp->m_right_node != nullptr)
		{
			visit_queue.push(temp->m_right_node);
		}
	}


}
template <typename T>
TreeNode<T>* BinaryTree<T>::MakeNode(T data)
{
	return new TreeNode<T>(data);
}
template <typename T>
TreeNode<T>* BinaryTree<T>::MakeNode()
{
	return new TreeNode<T>();
}