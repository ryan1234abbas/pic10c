#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <iomanip>

template<typename T> class BinarySearchTree;
template<typename T> class Iterator;
template<typename T> class BreadthFirstIterator;


template<typename T>
class Node
{
public:

private:
    T data;
    Node* left;
    Node* right;
    friend class BinarySearchTree<T>;
    friend class BreadthFirstIterator<T>;
    friend class Iterator<T>;
};


template<typename T>
class Iterator
{
public:
    /**
       Looks up the value at a position.
       @return the value of the node to which the iterator points
    */
    T get() const;
    /**
       Advances the iterator to the next node.
       Inorder Traversal
    */
    void next();
    /**
       Compares two iterators.
       @param other the iterator to compare with this iterator
       @return true if this iterator and other are equal
    */
    bool equals(const Iterator& other) const;
    bool isend() const;
    T operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator!=(const Iterator& other) const;
private:
    const BinarySearchTree<T>* container;
    std::stack<Node<T>*> nodeStack;
//Stack: Typically used for in - order, pre - order, or post - order traversal.
//Queue : Used for level - order traversal(BFS).

    friend class BinarySearchTree<T>;
};

template<typename T>
T Iterator<T>::get() const
{
    if (!nodeStack.empty())
    {
        return nodeStack.top()->data;
    }
    else
    {
        return T{};
    }
}

template<typename T>
void Iterator<T>::next()
{
    if (!nodeStack.empty())
    {
        Node<T>* current = nodeStack.top();
        nodeStack.pop();

        Node<T>* rightChild = current->right;
        while (rightChild != nullptr)
        {
            nodeStack.push(rightChild);
            rightChild = rightChild->left;
        }
    }
}

template<typename T>
bool Iterator<T>::equals(const Iterator& other) const
{
    if (nodeStack.size() != other.nodeStack.size()) {
        return false;
    }

    auto tempStack1 = nodeStack;
    auto tempStack2 = other.nodeStack;

    while (!tempStack1.empty()) {
        if (tempStack1.top() != tempStack2.top()) {
            return false;
        }
        tempStack1.pop();
        tempStack2.pop();
    }

    return true;
}

template<typename T>
bool Iterator<T>::isend() const
{
    return nodeStack.empty();
}

template<typename T>
T Iterator<T>::operator*() const { return get(); }

template<typename T>
Iterator<T>& Iterator<T>::operator++() { next(); return *this; }

template<typename T>
Iterator<T> Iterator<T>::operator++(int) { Iterator tmp = *this; next(); return tmp; }

template<typename T>
bool Iterator<T>::operator!=(const Iterator& other) const { return !equals(other); }


/*
   This class implements a binary search tree whose
   nodes hold strings.
*/
template<typename T = int>
class BinarySearchTree
{
public:
    /**
       Constructs an empty tree.
    */
    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);

    /**
       Inserts a new node into the tree.
       @param element the element to insert
    */
    void insert(T element);

    /**
       Tries to find an element in the tree.
       @param element the element to find
       @return 1 if the element is contained in the tree
    */
    int count(T element) const;

    /**
       Tries to remove an element from the tree. Does nothing
       if the element is not contained in the tree.
       @param element the element to remove
    */
    void erase(T element);

    /**
       Prints the contents of the tree in sorted order.
    */
    void print() const;

    /**
   Returns an iterator to the beginning of this BinarySearchTree.
   @return a BinarySearchTree iterator to the beginning
*/
    Iterator<T> begin() const;

    /**
       Returns an iterator past the end of this BinarySearchTree.
       @return a BinarySearchTree iterator past the end
    */
    Iterator<T> end() const;


    /**
Returns an BreadthFirstIterator to the beginning of this BinarySearchTree.
@return a BinarySearchTree iterator to the beginning
*/
    BreadthFirstIterator<T> Bbegin() const;

    /**
       Returns an BreadthFirstIterator past the end of this BinarySearchTree.
       @return a BinarySearchTree iterator past the end
    */
    BreadthFirstIterator<T> Bend() const;



private:
    /**
       Prints a node and all of its descendants in sorted order.
       @param parent the root of the subtree to print
    */
    void print(Node<T>* parent, int indent, char symbol) const;

    /**
       Inserts a new node as a descendant of a given node.
       @param parent the root node
       @param new_node the node to insert
    */
    void add_node(Node<T>* parent, Node<T>* new_node) const;
    void destroy(Node<T>* node);
    Node<T>* copy(Node<T>* node) const;

    Node<T>* root;
    friend class Iterator<T>;
    friend class BreadthFirstIterator<T>;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
    root = nullptr;
}

template<typename T>
void BinarySearchTree<T>::destroy(Node<T>* node)
{
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() { destroy(root); }

template<typename T>
Node<T>* BinarySearchTree<T>::copy(Node<T>* node) const
{
    if (node == nullptr) return nullptr;
    Node<T>* n = new Node<T>;
    n->data = node->data;
    n->left = copy(node->left);
    n->right = copy(node->right);
    return n;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other)
{
    root = copy(other.root);
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& other)
{
    if (this != &other)
    {
        destroy(root);
        root = copy(other.root);
    }
    return *this;
}

template<typename T>
void BinarySearchTree<T>::insert(T element)
{
    Node<T>* new_node = new Node<T>;
    new_node->data = element;
    new_node->left = nullptr;
    new_node->right = nullptr;
    if (root == nullptr) { root = new_node; }
    else { add_node(root, new_node); }
}

template<typename T>
int BinarySearchTree<T>::count(T element) const
{
    Node<T>* current = root;
    while (current != nullptr)
    {
        if (element < current->data)
        {
            current = current->left;
        }
        else if (element > current->data)
        {
            current = current->right;
        }
        else return 1;
    }
    return 0;
}

template<typename T>
void BinarySearchTree<T>::erase(T element)
{
    Node<T>* to_be_removed = root;
    Node<T>* parent = nullptr;
    bool found = false;
    while (!found && to_be_removed != nullptr)
    {
        if (element == to_be_removed->data)
        {
            found = true;
        }
        else
        {
            parent = to_be_removed;
            if (element < to_be_removed->data)
            {
                to_be_removed = to_be_removed->left;
            }
            else
            {
                to_be_removed = to_be_removed->right;
            }
        }
    }

    if (!found) { return; }

    if (to_be_removed->left == nullptr || to_be_removed->right == nullptr)
    {
        Node<T>* new_child;
        if (to_be_removed->left == nullptr)
        {
            new_child = to_be_removed->right;
        }
        else
        {
            new_child = to_be_removed->left;
        }

        if (parent == nullptr)
        {
            root = new_child;
        }
        else if (parent->left == to_be_removed)
        {
            parent->left = new_child;
        }
        else
        {
            parent->right = new_child;
        }
        return;
    }

    Node<T>* smallest_parent = to_be_removed;
    Node<T>* smallest = to_be_removed->right;
    while (smallest->left != nullptr)
    {
        smallest_parent = smallest;
        smallest = smallest->left;
    }

    to_be_removed->data = smallest->data;
    if (smallest_parent == to_be_removed)
    {
        smallest_parent->right = smallest->right;
    }
    else
    {
        smallest_parent->left = smallest->right;
    }
}

template<typename T>
void BinarySearchTree<T>::print() const
{
    print(root,0,' ');
    std::cout << std::endl;
}

template<typename T>
void BinarySearchTree<T>::print(Node<T>* parent, int indent, char symbol) const
{
    if (parent == nullptr) { return; }
    print(parent->right, indent + 4, '/');
    std::cout << std::setw(indent) << symbol << parent->data << std::endl;
    print(parent->left, indent + 4, '\\');
}

template<typename T>
void BinarySearchTree<T>::add_node(Node<T>* parent, Node<T>* new_node) const
{
    if (new_node->data < parent->data)
    {
        if (parent->left == nullptr) { parent->left = new_node; }
        else { add_node(parent->left, new_node); }
    }
    else if (new_node->data > parent->data)
    {
        if (parent->right == nullptr) { parent->right = new_node; }
        else { add_node(parent->right, new_node); }
    }
}

template<typename T>
Iterator<T> BinarySearchTree<T>::begin() const
{
    Iterator<T> iter;
    Node<T>* current = root;
    while (current != nullptr)
    {
        iter.nodeStack.push(current);
        current = current->left;
    }

    iter.container = this;
    return iter;
}

template<typename T>
Iterator<T> BinarySearchTree<T>::end() const
{
    Iterator<T> iter;
    iter.container = this;
    return iter;
}

template<typename T>
Iterator<T> begin(const BinarySearchTree<T>& tree) { return tree.begin(); }

template<typename T>
Iterator<T> end(const BinarySearchTree<T>& tree) { return tree.end(); }


/**
   This iterator visits the nodes of a tree in
   breadth-first order.
*/
template<typename T>
class BreadthFirstIterator
{
public:
    /**
       Constructs an iterator for a given tree.
       @param root the root of the tree
    */
    BreadthFirstIterator(Node<T>* root);
    /**
       Gets the element to which this iterator points.
       @return the element
    */
    T get() const;
    /**
       Advances this iterator to the next position.
    */
    void next();
    bool equals(const BreadthFirstIterator& other) const;
    bool isend() const;
private:
    std::queue<Node<T>*> q;
};

template<typename T>
BreadthFirstIterator<T>::BreadthFirstIterator(Node<T>* root)
{
    if (root != nullptr) { q.push(root); }
}

template<typename T>
T BreadthFirstIterator<T>::get() const
{
    return q.front()->data;
}

template<typename T>
void BreadthFirstIterator<T>::next()
{
    Node<T>* n = q.front();
    q.pop();
    if(n->left!=nullptr){ q.push(n->left); }
    if (n->right != nullptr) { q.push(n->right); }
}

template<typename T>
bool BreadthFirstIterator<T>::equals(const BreadthFirstIterator& other) const
{
    return q.size() == 0 && other.q.size() == 0
        || q.size() > 0 && other.q.size() > 0
        && q.front() == other.q.front();
}

template<typename T>
bool BreadthFirstIterator<T>::isend() const {
    return q.empty();
}

template<typename T>
BreadthFirstIterator<T> BinarySearchTree<T>::Bbegin() const
{
    return BreadthFirstIterator<T>(root);
}

template<typename T>
BreadthFirstIterator<T> BinarySearchTree<T>::Bend() const
{
    return BreadthFirstIterator<T>(nullptr);
}

#endif