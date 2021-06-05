/*****************************************
* Author: Emmett Hale
*
* Purpose: Balanced Binary Search Tree
*
* Date Created: 6/2/2021
*****************************************/
#pragma once
#include "BinaryTree.h"

template <typename T>
class AVLTree : public BinaryTree<T>
{
public:
	AVLTree();
	AVLTree(T data);
	AVLTree(const AVLTree<T>& copy);
	AVLTree<T>& operator=(const AVLTree<T>& rhs);
	~AVLTree();

	void AddNode(const T& data);
	void RemoveNode(const T& data);
private:
	TreeNode<T>* LeftRotation(TreeNode<T>* root, bool sub_rotate = false);
	TreeNode<T>* RightRotation(TreeNode<T>* root, bool sub_rotate = false);
	TreeNode<T>* SubAdd(TreeNode<T>* node, T data);
};

/*****************************************
* Default Ctor
*****************************************/
template <typename T>
AVLTree<T>::AVLTree() : BinaryTree<T>()
{	}

/*****************************************
* One Arg Ctor
*****************************************/
template <typename T>
AVLTree<T>::AVLTree(T data) : BinaryTree<T>(data)
{	}

/*****************************************
* Deep Copy Ctor
*****************************************/
template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& copy) : BinaryTree<T>(copy)
{	}

/*****************************************
* Deep copy assignment operator
*****************************************/
template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& rhs) 
{
	if (this != &rhs)
	{
		BinaryTree<T>::operator=(rhs);
	}

	return *this;
}

/*****************************************
* Dtor
*****************************************/
template <typename T>
AVLTree<T>::~AVLTree()
{
}

template <typename T>
void AVLTree<T>::AddNode(const T& data)
{
	if(BinaryTree<T>::m_root == nullptr)
	{
		BinaryTree<T>::m_root = BinaryTree<T>::MakeNode(data);
	}
	else
	{
		BinaryTree<T>::m_root = SubAdd(BinaryTree<T>::m_root, data);
	}
}

template <typename T>
TreeNode<T> * AVLTree<T>::SubAdd(TreeNode<T>* node, T data)
{
	TreeNode<T>* to_return = node; //Return the root node after adding

	if (data < node->m_data) //Go Left
	{
		if (node->m_left_node == nullptr)
		{
			node->m_left_node = BinaryTree<T>::MakeNode(data);
			node->m_weight--;
		}
		else
		{
			int last_weight = node->m_left_node->m_weight;

			node->m_left_node = SubAdd(node->m_left_node, data);

			//Rotation if necessary
			//if the weight went from balanced to heavy, that side got longer
			//change our own weight
			if (node->m_left_node->m_weight != 0 && last_weight == 0) 
			{

				if (node->m_weight == -1) //We are unbalanced
				{
					//Rotate

					if (node->m_left_node->m_weight == -1) //LL
					{
						to_return = RightRotation(node);
					}
					else //LR
					{
						node->m_left_node = LeftRotation(node->m_left_node, true);
						to_return = RightRotation(node);
					}
				}
				else
				{
					node->m_weight--;
				}
			}
		}
	}
	else // Go Right
	{
		if (node->m_right_node == nullptr)
		{
			node->m_right_node = BinaryTree<T>::MakeNode(data);
			node->m_weight++;
		}
		else
		{
			int last_weight = node->m_right_node->m_weight;

			node->m_right_node = SubAdd(node->m_right_node, data);

			//Rotation if necessary
			//if the weight went from balanced to heavy, that side got longer
			//change our own weight
			if (node->m_right_node->m_weight != 0 && last_weight == 0)
			{

				if (node->m_weight == 1) //We are unbalanced
				{
					//Rotate

					if (node->m_right_node->m_weight == 1) //RR
					{
						to_return = LeftRotation(node);
					}
					else //RL
					{
						node->m_right_node = RightRotation(node->m_right_node, true);
						to_return = LeftRotation(node);
					}
				}
				else
				{
					node->m_weight++;
				}
			}
		}
	}

	return to_return;
}

template <typename T>
void AVLTree<T>::RemoveNode(const T& data)
{
	//This is annoying do it later
}

template <typename T>
TreeNode<T>* AVLTree<T>::RightRotation(TreeNode<T>* root, bool sub_rotate)
{
	TreeNode<T>* old_right = root->m_left_node->m_right_node;
	TreeNode<T>* new_root = root->m_left_node;


	//Change root weight based on type of rotation
	if (sub_rotate)
	{
		if (new_root->m_weight == -1)
		{
			root->m_weight += 2;
		}
		else
		{
			root->m_weight++;
		}
	}
	else
	{
		if (new_root->m_weight == -2)
		{
			root->m_weight += 2;
		}
		else
		{
			root->m_weight++;
		}
	}

	//If new root was balance, we were part of LR rotation
	if (new_root->m_weight != -2 && new_root->m_weight != 0)
	{
		new_root->m_weight++;
	}
	else if(new_root->m_weight != 0)
	{
		new_root->m_weight += 2;
	}

	//Rotate
	root->m_left_node->m_right_node = root;
	root->m_left_node = old_right;

	return new_root;
}

template <typename T>
TreeNode<T>* AVLTree<T>::LeftRotation(TreeNode<T>* root, bool sub_rotate)
{
	TreeNode<T>* old_left = root->m_right_node->m_left_node;
	TreeNode<T>* new_root = root->m_right_node;

	//Change root weight based on type of rotation
	if (sub_rotate)
	{
		if (new_root->m_weight == 1)
		{
			root->m_weight -= 2;
		}
		else
		{
			root->m_weight--;
		}
	}
	else
	{
		if (new_root->m_weight == 2)
		{
			root->m_weight -= 2;
		}
		else
		{
			root->m_weight--;
		}
	}

	//If new root was balance, we were part of RL rotation
	if (new_root->m_weight != 2 && new_root->m_weight != 0)
	{
		new_root->m_weight--;
	}
	else if (new_root->m_weight != 0)
	{
		new_root->m_weight -= 2;
	}

	//Rotate
	root->m_right_node->m_left_node = root;
	root->m_right_node = old_left;

	return new_root;
}

