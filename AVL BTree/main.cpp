/*****************************************
* Author: Emmett Hale
* 
* Purpose: Stub file for testing AVL BTree
* 
* Date Created: 6/2/2021
*****************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::endl;

#include "AVLBinaryTree.h"

void Print(const int& text);

int main()
{
	//Memory leak checking nonsense
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	BinaryTree<int> * tree1 = new BinaryTree<int>(50);
	tree1->AddNode(70);
	tree1->AddNode(30);

	tree1->AddNode(40);
	tree1->AddNode(60);
	tree1->AddNode(35);
	tree1->AddNode(65);

	BinaryTree<int> tree2(*tree1);

	tree1->RemoveNode(40);
	tree1->RemoveNode(30);
	tree1->RemoveNode(70);
	tree1->RemoveNode(60);
	tree1->RemoveNode(35);
	tree1->RemoveNode(65);
	tree1->RemoveNode(50);

	*tree1 = tree2;

	cout << "Height: "<< tree1->GetHeight() << endl;
	cout << "\nDepth First: " << endl;
	tree1->DepthTraverse(Print);
	cout << "\nBreadth First: " << endl;
	tree1->BreadthTraverse(Print);

	delete tree1;

	AVLTree<int> avl_tree1;
	AVLTree<int> *avl_tree2 = new AVLTree<int>(100);
	AVLTree<int> avl_tree3(*avl_tree2);

	//Test LL
	avl_tree1.AddNode(3);
	avl_tree1.AddNode(2);
	avl_tree1.AddNode(1);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();
	
	//Test RR
	avl_tree1.AddNode(1);
	avl_tree1.AddNode(2);
	avl_tree1.AddNode(3);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();

	//Test RL
	avl_tree1.AddNode(3);
	avl_tree1.AddNode(1);
	avl_tree1.AddNode(2);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();

	//Test LR
	avl_tree1.AddNode(1);
	avl_tree1.AddNode(3);
	avl_tree1.AddNode(2);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();

	//Test RL but bigger
	avl_tree1.AddNode(10);
	avl_tree1.AddNode(20);
	avl_tree1.AddNode(3);
	avl_tree1.AddNode(5);
	avl_tree1.AddNode(2);
	avl_tree1.AddNode(15);
	avl_tree1.AddNode(4);
	avl_tree1.AddNode(7);
	avl_tree1.AddNode(1);
	avl_tree1.AddNode(6);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();

	//Test RL but bigger again
	avl_tree1.AddNode(10);
	avl_tree1.AddNode(20);
	avl_tree1.AddNode(3);
	avl_tree1.AddNode(6);
	avl_tree1.AddNode(2);
	avl_tree1.AddNode(15);
	avl_tree1.AddNode(5);
	avl_tree1.AddNode(7);
	avl_tree1.AddNode(1);
	avl_tree1.AddNode(4);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();


	//Test LR but bigger
	avl_tree1.AddNode(5);
	avl_tree1.AddNode(4);
	avl_tree1.AddNode(10);
	avl_tree1.AddNode(3);
	avl_tree1.AddNode(20);
	avl_tree1.AddNode(7);
	avl_tree1.AddNode(6);
	avl_tree1.AddNode(8);
	avl_tree1.AddNode(21);
	avl_tree1.AddNode(9);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();

	//Test LR but bigger again
	avl_tree1.AddNode(5);
	avl_tree1.AddNode(4);
	avl_tree1.AddNode(10);
	avl_tree1.AddNode(3);
	avl_tree1.AddNode(20);
	avl_tree1.AddNode(8);
	avl_tree1.AddNode(9);
	avl_tree1.AddNode(7);
	avl_tree1.AddNode(21);
	avl_tree1.AddNode(6);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();

	//Bigger LL
	avl_tree1.AddNode(5);
	avl_tree1.AddNode(3);
	avl_tree1.AddNode(6);
	avl_tree1.AddNode(4);
	avl_tree1.AddNode(2);
	avl_tree1.AddNode(1);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();

	//Bigger RR
	avl_tree1.AddNode(2);
	avl_tree1.AddNode(1);
	avl_tree1.AddNode(4);
	avl_tree1.AddNode(3);
	avl_tree1.AddNode(5);
	avl_tree1.AddNode(6);

	cout << "\nBreadth First: " << endl;
	avl_tree1.BreadthTraverse(Print);

	avl_tree1.ClearTree();

	avl_tree1 = avl_tree3;

	delete avl_tree2;

	return 0;
}

void Print(const int& text)
{
	cout << text << endl;
}