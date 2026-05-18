#include "red_black_tree.h"
#include<iomanip> 
#include <iostream>



Node::Node()
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = RED;
}


/*Nodes in a red - black tree also have a link to the parent.
When adding or moving a node, 
it is important that the parent and child links are synchronized.
Because this synchronization is tedious and error-prone,
we provide several helper functions:
set_left_child, set_right_child,replace_with
*/
void Node::set_left_child(Node* child)
{
    left = child;
    if (child != nullptr) { child->parent = this; }
}

void Node::set_right_child(Node* child)
{
    right = child;
    if (child != nullptr) { child->parent = this; }
}

void RedBlackTree::replace_with(Node* to_be_replaced, Node* replacement)
{
    if (to_be_replaced->parent == nullptr)
    {
        replacement->parent = nullptr;
        root = replacement;
    }
    else if (to_be_replaced == to_be_replaced->parent->left)
    {
        to_be_replaced->parent->set_left_child(replacement);
    }
    else
    {
        to_be_replaced->parent->set_right_child(replacement);
    }
}


RedBlackTree::RedBlackTree()
{
    root = nullptr;
}

void RedBlackTree::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

RedBlackTree::~RedBlackTree()
{
    destroyTree(root);
}


//copy constructor
static Node* deepCopy(Node* n, Node* parent)
{
    if (n == nullptr) return nullptr;
    Node* newNode = new Node;
    newNode->data   = n->data;
    newNode->color  = n->color;
    newNode->parent = parent;
    newNode->left   = deepCopy(n->left,  newNode);
    newNode->right  = deepCopy(n->right, newNode);
    return newNode;
}

RedBlackTree::RedBlackTree(const RedBlackTree& other)
{
    root = deepCopy(other.root, nullptr);
}

RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other)
{
    if (this != &other) {
        destroyTree(root);
        root = deepCopy(other.root, nullptr);
    }
    return *this;
}


/*Insertion is handled as it is in a binary search tree.
We insert a red node. Afterward, we call a function that
fixes up the tree so it is a red-black tree again:
*/

//insert
void RedBlackTree::insert(std::string element)
{
    Node* new_node = new Node;
    new_node->data  = element;
    new_node->color = RED;
    new_node->left  = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;

    if (root == nullptr) root = new_node;
    else root->add_node(new_node);

    fix_after_add(new_node);
}

void RedBlackTree::fix_after_add(Node* new_node)
{
    if (new_node->parent == nullptr) {
        new_node->color = BLACK;
        return;
    }
    if (new_node->parent->color == RED)
        fix_double_red(new_node);
}

//double red
void RedBlackTree::fix_double_red(Node* child)
{
    Node* parent = child->parent;
    if (parent == nullptr) return;
    Node* grandparent = parent->parent;
    if (grandparent == nullptr) { parent->color = BLACK; return; }

    Node* n1, *n2, *n3;
    Node* t1, *t2, *t3, *t4;
    bool gp_is_double_black = (grandparent->color == DOUBLE_BLACK);

    if (grandparent->left == parent && parent->left == child) {
        //LL
        n1=child; n2=parent; n3=grandparent;
        t1=child->left; t2=child->right; t3=parent->right; t4=grandparent->right;
    } else if (grandparent->left == parent && parent->right == child) {
        //LR
        n1=parent; n2=child; n3=grandparent;
        t1=parent->left; t2=child->left; t3=child->right; t4=grandparent->right;
    } else if (grandparent->right == parent && parent->left == child) {
        //RL
        n1=grandparent; n2=child; n3=parent;
        t1=grandparent->left; t2=child->left; t3=child->right; t4=parent->right;
    } else {
        //RR
        n1=grandparent; n2=parent; n3=child;
        t1=grandparent->left; t2=parent->left; t3=child->left; t4=child->right;
    }

    Node* gp_parent   = grandparent->parent;
    bool gp_was_left   = (gp_parent != nullptr && gp_parent->left == grandparent);

    // if grandparent was double-black, n2 absorbs it -> black
    // otherwise normal: n2=red, n1=black, n3=black
    n2->color = gp_is_double_black ? BLACK : RED;
    n1->color = BLACK;
    n3->color = BLACK;

    n2->set_left_child(n1);   n2->set_right_child(n3);
    n1->set_left_child(t1);   n1->set_right_child(t2);
    n3->set_left_child(t3);   n3->set_right_child(t4);

    if (gp_parent == nullptr) { n2->parent = nullptr; root = n2; }
    else if (gp_was_left)       gp_parent->set_left_child(n2);
    else                         gp_parent->set_right_child(n2);

    if (n2->parent != nullptr && n2->parent->color == RED)
        fix_double_red(n2);
    else if (n2->parent == nullptr)
        n2->color = BLACK;
}

//erase
void RedBlackTree::erase(std::string element)
{
    Node* to_be_removed = root;
    while (to_be_removed != nullptr) {
        if      (element < to_be_removed->data) to_be_removed = to_be_removed->left;
        else if (element > to_be_removed->data) to_be_removed = to_be_removed->right;
        else break;
    }
    if (to_be_removed == nullptr) return;

    if (to_be_removed->left == nullptr || to_be_removed->right == nullptr) {
        fix_before_remove(to_be_removed);
        Node* new_child = (to_be_removed->left != nullptr)
                          ? to_be_removed->left : to_be_removed->right;
        replace_with(to_be_removed, new_child);
        delete to_be_removed;
    } else {
        Node* smallest = to_be_removed->right;
        while (smallest->left != nullptr) smallest = smallest->left;
        to_be_removed->data = smallest->data;
        fix_before_remove(smallest);
        replace_with(smallest, smallest->right);
        delete smallest;
    }
}

void RedBlackTree::fix_before_remove(Node* to_be_removed)
{
    if (to_be_removed->color == RED) return; // Case 1: red, safe

    if (to_be_removed->left != nullptr || to_be_removed->right != nullptr) {
        Node* child = (to_be_removed->left != nullptr)
                      ? to_be_removed->left : to_be_removed->right;
        child->color = BLACK;
        return;
    }
    bubble_up(to_be_removed->parent);
}

//bubble up
void RedBlackTree::bubble_up(Node* parent)
{
    if (parent == nullptr) return;

    parent->color += 1;
    if (parent->left  != nullptr) parent->left->color  -= 1;
    if (parent->right != nullptr) parent->right->color -= 1;

    if (parent->left  != nullptr) bubble_up_fix(parent->left);
    if (parent->right != nullptr) bubble_up_fix(parent->right);

    if (parent->color == DOUBLE_BLACK) {
        if (parent->parent == nullptr) parent->color = BLACK; // root
        else bubble_up(parent->parent);
    }
}

bool RedBlackTree::bubble_up_fix(Node* child)
{
    if (child->color == NEGATIVE_RED) {
        fix_negative_red(child);
        return true;
    } else if (child->color == RED) {
        if (child->left  != nullptr && child->left->color  == RED)
            { fix_double_red(child->left);  return true; }
        if (child->right != nullptr && child->right->color == RED)
            { fix_double_red(child->right); return true; }
    }
    return false;
}

//neg red
void RedBlackTree::fix_negative_red(Node* neg_red)
{
    Node* db_parent = neg_red->parent;
    Node* gp        = db_parent->parent;
    bool db_is_left = (gp != nullptr && gp->left == db_parent);

    Node* n1, *n2, *n3;
    Node* t1, *t2, *t3, *t4;

    if (db_parent->right == neg_red) {
        // neg_red is right child
        n1=db_parent; n2=neg_red->left; n3=neg_red;
        t1=db_parent->left; t2=n2->left; t3=n2->right; t4=neg_red->right;
    } else {
        // neg_red is left child
        n1=neg_red; n2=neg_red->right; n3=db_parent;
        t1=neg_red->left; t2=n2->left; t3=n2->right; t4=db_parent->right;
    }

    n2->color = BLACK; n1->color = RED; n3->color = RED;

    n2->set_left_child(n1);  n2->set_right_child(n3);
    n1->set_left_child(t1);  n1->set_right_child(t2);
    n3->set_left_child(t3);  n3->set_right_child(t4);

    if      (gp == nullptr)  { n2->parent = nullptr; root = n2; }
    else if (db_is_left)       gp->set_left_child(n2);
    else                        gp->set_right_child(n2);

    bubble_up_fix(n1);
    bubble_up_fix(n3);
}


void RedBlackTree::print() const
{
    print(root, 0, ' ');
    std::cout << std::endl;
}
void RedBlackTree::print(Node* parent, int indent, char symbol) const
{
    if (parent == nullptr) { return; }
    print(parent->right, indent + 3, '/');
    // Print right subtree with increased indentation

    if (parent->color == RED)
    {
        std::cout << std::setw(indent) << symbol << "R" << parent->data << std::endl;
    }
    else
    {
        std::cout << std::setw(indent) << symbol << "B" << parent->data << std::endl;
    }
    // Print current node with indentation
    print(parent->left, indent + 3, '\\');
    // Print left subtree with increased indentation
}


int RedBlackTree::count(std::string element) const
{
    Node* current = root;
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



void Node::add_node(Node* new_node)
{
    if (new_node->data < data)
    {
        if (left == nullptr)
        {
            left = new_node;
            left->parent = this;
        }
        else { left->add_node(new_node); }
    }
    else if (new_node->data > data)
    {
        if (right == nullptr)
        {
            right = new_node;
            right->parent = this;
        }
        else { right->add_node(new_node); }
    }
}




