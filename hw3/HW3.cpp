#include <iostream>
#include <string>
#include <vector>

#include "binary_search_tree.h" 

int main()
{
	std::string s(10000, '*');
	for (int i = 1;i < 100000;i++)
	{
		BinarySearchTree* tpt;
		tpt = new BinarySearchTree;
		for (int j = 0;j < i % 197;j++)
		{
			tpt->insert(std::to_string(j)+s);
		}
		delete tpt;
	}
//Without a destructor, this loop uses about 400GB of memory 
	Node n1;
	std::cout << n1.ncall << std::endl;
	BinarySearchTree tree;
	tree.insert("B");
	tree.insert("D");
	tree.insert("A");
	tree.insert("Z");
	tree.insert("F");
	tree.insert("I");
	tree.insert("E");
	tree.insert("E");
	std::cout << n1.ncall << std::endl;
	BinarySearchTree tree2=tree;
        BinarySearchTree *treeptr=new BinarySearchTree;
        (*treeptr)=tree2;
        delete treeptr;
	tree2.print();
	std::cout << n1.ncall << std::endl;
         return 0;
}