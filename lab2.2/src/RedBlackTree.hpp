//
// Created by Ivan Ramyk on 3/21/20.
//

#ifndef ALGORITHMS_REDBLACKTREE_HPP
#define ALGORITHMS_REDBLACKTREE_HPP

#include "Tree.hpp"

#include <string>
#include <vector>



enum color {
    RED, BLACK
};
template <typename TreeItem>
class RedBlackTree;

template <typename TreeItem>
class RedBlackTreeNode:Node<TreeItem>{
private:
    TreeItem _value;
    RedBlackTreeNode<TreeItem> * _left;
    RedBlackTreeNode<TreeItem> * _right;
    RedBlackTreeNode<TreeItem> * _parent;
    color _color;
    int _size;
public:
    explicit RedBlackTreeNode<TreeItem> (
            TreeItem item,
            RedBlackTreeNode<TreeItem> * left = nullptr,
            RedBlackTreeNode<TreeItem> * right = nullptr,
            RedBlackTreeNode<TreeItem> * parent = nullptr);

    TreeItem value();

    friend class RedBlackTree<TreeItem>;

    Node<TreeItem> * next();
};

template <typename TreeItem>
class RedBlackTree {
private:
    RedBlackTreeNode <TreeItem> * _root;
    void _leftRotate(RedBlackTreeNode<TreeItem> * node);

    void _rightRotate(RedBlackTreeNode<TreeItem> * node);

    void _fixInsertion(RedBlackTreeNode<TreeItem> * node);

    void _print(RedBlackTreeNode<TreeItem> * node, std::vector<std::pair<TreeItem, TreeItem>> &events);

    void _fixDeleting(RedBlackTreeNode <TreeItem> * x);

    int _height(RedBlackTreeNode<TreeItem> * node);

    RedBlackTreeNode<TreeItem> * _select(RedBlackTreeNode<TreeItem> * node, int k);

    void _fixSize(RedBlackTreeNode<TreeItem> * node);

    int _updateSize(RedBlackTreeNode<TreeItem> * node);

    void _updateNode(RedBlackTreeNode<TreeItem> * node);

public:
    RedBlackTree();

    void insert(TreeItem item);

    RedBlackTreeNode <TreeItem> * search(TreeItem item);

    std::vector<std::pair<TreeItem, TreeItem>> print();

    void remove(RedBlackTreeNode <TreeItem> * z);

    int height();

    RedBlackTreeNode<TreeItem> * select(int k);

    void updateSize();

    int order(RedBlackTreeNode <TreeItem> * node);

    TreeIterator<TreeItem> begin(){
        if (_root == nullptr)
            return TreeIterator<TreeItem>(nullptr);
        RedBlackTreeNode<TreeItem> * cur = _root;
        while (cur->_left != nullptr)
            cur = cur->_left;
        return TreeIterator<TreeItem>(cur);
    }

    TreeIterator<TreeItem> end(){
        return nullptr;
    }
};

template<typename TreeItem>
void RedBlackTree<TreeItem>::insert(TreeItem item) {
    if (_root == nullptr){
        _root = new RedBlackTreeNode<TreeItem>(item);
        _root->_color = BLACK;
        _root->_size = 1;
    }
    else {
        RedBlackTreeNode<TreeItem> *current_node = _root;
        RedBlackTreeNode<TreeItem> *previous_node = nullptr;
        while (current_node != nullptr) {
            current_node->_size++;
            if (item < current_node->_value) {
                previous_node = current_node;
                current_node = current_node->_left;
            } else {
                previous_node = current_node;
                current_node = current_node->_right;
            }
        }
        current_node = new RedBlackTreeNode<TreeItem>(item);
        current_node->_parent = previous_node;
        if (item < previous_node->_value){
            previous_node->_left = current_node;
        }
        else {
            previous_node->_right = current_node;
        }
        _fixInsertion(current_node);
    }
}

template<typename TreeItem>
void RedBlackTree<TreeItem>::_fixInsertion(RedBlackTreeNode<TreeItem> *node) {
    while (node->_parent != nullptr && node->_parent->_color == RED){
        if (node->_parent == node->_parent->_parent->_left){
            if (node->_parent->_parent->_right != nullptr){
                if (node->_parent->_parent->_right->_color == RED){
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_right->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    node = node->_parent->_parent;
                }
                else {
                    if (node == node->_parent->_right){
                        node = node->_parent;
                        _leftRotate(node);
                    }
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    _rightRotate(node->_parent->_parent);
                }
            }
            else {
                    if (node == node->_parent->_right){
                        node = node->_parent;
                        _leftRotate(node);
                    }
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    _rightRotate(node->_parent->_parent);
            }
        }
        else {
            if (node->_parent->_parent->_left != nullptr){
                if (node->_parent->_parent->_left->_color == RED){
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_left->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    node = node->_parent->_parent;
                }
                else {
                    if (node->_parent->_left == node){
                        node = node->_parent;//tuta ostanovilsia
                        _rightRotate(node);
                    }
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    _leftRotate(node->_parent->_parent);
                }
            }
            else {
                if (node->_parent->_left == node){
                    node = node->_parent;//tuta ostanovilsia
                    _rightRotate(node);
                }
                node->_parent->_color = BLACK;
                node->_parent->_parent->_color = RED;
                _leftRotate(node->_parent->_parent);
            }
        }
    }
    _root->_color = BLACK;
}

template<typename TreeItem>
RedBlackTreeNode<TreeItem> *RedBlackTree<TreeItem>::search(TreeItem item) {
    RedBlackTreeNode <TreeItem> * node  = _root;
    while (node != nullptr && node->_value != item){
        if (item < node->_value)
            node = node->_left;
        else
            node = node->_right;
    }
    return node;
}

template<typename TreeItem>
void RedBlackTree<TreeItem>::_fixDeleting(RedBlackTreeNode<TreeItem> *x) {
    if (x == nullptr)
        return;
    while (x != _root && x->_color == BLACK) {
        if (x == x->_parent->_left) {
            RedBlackTreeNode <TreeItem> * w = x->_parent->_right;
            if (w->_color == RED) {
                w->_color = BLACK;
                x->_parent->_color = RED;
                _leftRotate (x->_parent);
                w = x->_parent->_right;
            }
            if (w->_left->_color == BLACK && w->_right->_color == BLACK) {
                w->_color = RED;
                x = x->_parent;
            } else {
                if (w->_right->_color == BLACK) {
                    w->_left->_color = BLACK;
                    w->_color = RED;
                    _rightRotate (w);
                    w = x->_parent->_right;
                }
                w->_color = x->_parent->_color;
                x->_parent->_color = BLACK;
                w->_right->_color = BLACK;
                _leftRotate (x->_parent);
                x = _root;
            }
        } else {
            RedBlackTreeNode <TreeItem> * w = x->_parent->_left;
            if (w->_color == RED) {
                w->_color = BLACK;
                x->_parent->_color = RED;
                _rightRotate(x->_parent);
                w = x->_parent->_left;
            }
            if (w->_right->_color == BLACK && w->_left->_color == BLACK) {
                w->_color = RED;
                x = x->_parent;
            } else {
                if (w->_left->_color == BLACK) {
                    w->_right->_color = BLACK;
                    w->_color = RED;
                    _leftRotate(w);
                    w = x->_parent->_left;
                }
                w->_color = x->_parent->_color;
                x->_parent->_color = BLACK;
                w->_left->_color = BLACK;
                _rightRotate (x->_parent);
                x = _root;
            }
        }
    }
    x->_color = BLACK;
}

template<typename TreeItem>
std::vector<std::pair<TreeItem, TreeItem>> RedBlackTree<TreeItem>::print() {
    std::vector<std::pair<TreeItem, TreeItem>> events;
    _print(_root, events);
    return events;
}

template<typename TreeItem>
void RedBlackTree<TreeItem>::_leftRotate(RedBlackTreeNode<TreeItem> *node) {
    RedBlackTreeNode<TreeItem> * y = node->_right;
    y->_size = node->_size;
    RedBlackTreeNode<TreeItem> * x = y->_left;
    y->_parent = node->_parent;
    if (node->_parent == nullptr){
        _root = y;
    }
    else if (node == node->_parent->_left){
        node->_parent->_left = y;
    }
    else node->_parent->_right = y;
    node->_parent = y;
    y->_left = node;
    node->_right = x;
    node->_size = 1;
    if (node->_left)
        node->_size += node->_left->_size;
    if (node->_right)
        node->_size += node->_right->_size;
    if (x != nullptr)
        x->_parent = node;
}

template<typename TreeItem>
void RedBlackTree<TreeItem>::_rightRotate(RedBlackTreeNode<TreeItem> *node) {
    RedBlackTreeNode<TreeItem> * y = node->_left;
    y->_size = node->_size;
    RedBlackTreeNode<TreeItem> * x = y->_right;
    y->_parent = node->_parent;
    if (node->_parent == nullptr){
        _root = y;
    }
    else if (node == node->_parent->_left){
        node->_parent->_left = y;
    }
    else node->_parent->_right = y;
    node->_parent = y;
    y->_right = node;
    node->_left = x;
    node->_size = 1;
    if (node->_left)
        node->_size += node->_left->_size;
    if (node->_right)
        node->_size += node->_right->_size;
    if (x != nullptr)
        x->_parent = node;
}

template<typename TreeItem>
void RedBlackTree<TreeItem>::_print(RedBlackTreeNode<TreeItem> *node, std::vector<std::pair<TreeItem, TreeItem>> &events) {
    if (node == nullptr)
        return;
    if (node->_left != nullptr){
        events.push_back({node->value(),node->_left->value()});
        _print(node->_left, events);
    }
    if (node->_right != nullptr){
        events.push_back({node->value(),node->_right->value()});
        _print(node->_right, events);
    }
}

template<typename TreeItem>
void RedBlackTree<TreeItem>::remove(RedBlackTreeNode<TreeItem> *z) {
    //_fixSize(z);
    RedBlackTreeNode <TreeItem> *x, *y;
    if (z == nullptr) return;
    if (z->_left == nullptr || z->_right == nullptr) {
        /* y has a NIL node as a child */
        y = z;
    } else {
        /* find tree successor with a NIL node as a child */
        y = z->_right;
        while (y->_left != nullptr) y = y->_left;
    }// y == 6?
    _fixSize(y);
    /* x is y's only child */
    if (y->_left != nullptr)
        x = y->_left;
    else
        x = y->_right;//x == null
    /* remove y from the parent chain */
    if (x != nullptr)
        x->_parent = y->_parent;
    if (y->_parent != nullptr)
        if (y == y->_parent->_left)
            y->_parent->_left = x;
        else
            y->_parent->_right = x;
    else
        _root = x;
    if (y != z)
        z->_value = y->value();


    if (y->_color == BLACK)
        _fixDeleting (x);

    delete y;
}

template<typename TreeItem>
RedBlackTree<TreeItem>::RedBlackTree() {
    _root = nullptr;
}

template<typename TreeItem>
int RedBlackTree<TreeItem>::_height(RedBlackTreeNode<TreeItem> *node) {
    if (node == nullptr)
        return 0;
    return std::max(_height(node->_left), _height(node->_right)) + 1;
}

template<typename TreeItem>
int RedBlackTree<TreeItem>::height() {
    return _height(_root);
}

template<typename TreeItem>
RedBlackTreeNode<TreeItem> *RedBlackTree<TreeItem>::select(int k) {
    if (_root == nullptr || _root->_size < k)
        return nullptr;
    return _select(_root, k);
}

template<typename TreeItem>
RedBlackTreeNode<TreeItem> *RedBlackTree<TreeItem>::_select(RedBlackTreeNode<TreeItem> *node, int k) {
    int r = 1;
    if (node->_left != nullptr)
        r = node->_left->_size + 1;
    if (r == k)
        return node;
    if (k < r)
        return _select(node->_left, k);
    return _select(node->_right, k - r);
}

template<typename TreeItem>
void RedBlackTree<TreeItem>::updateSize() {
    _updateSize(_root);
}

template<typename TreeItem>
void RedBlackTree<TreeItem>::_fixSize(RedBlackTreeNode<TreeItem> *node) {
    if (node == nullptr)
        return;
    node->_size--;
    _fixSize(node->_parent);
}

template<typename TreeItem>
int RedBlackTree<TreeItem>::_updateSize(RedBlackTreeNode<TreeItem> *node) {
    if (node == nullptr) return 0;
    return node->_size = _updateSize(node->_left) + _updateSize(node->_right) + 1;
}

template<typename TreeItem>
void RedBlackTree<TreeItem>::_updateNode(RedBlackTreeNode<TreeItem> *node) {
    if (node == nullptr)
        return;
    node->_size = 1;
    if (node->_left)
        node->_size += node->_left->_size;
    if (node->_right)
        node->_size += node->_right->_size;
}

template<typename TreeItem>
int RedBlackTree<TreeItem>::order(RedBlackTreeNode<TreeItem> *node) {
    int r = 1;
    if (node->_left != nullptr)
        r += node->_left->_size;
    RedBlackTreeNode <TreeItem> * cur = node;
    while (cur->_parent != nullptr){
        if (cur->_parent->_right == cur){
            r += 1;
            if (cur->_parent->_left)
                r += cur->_parent->_left->_size;
        }
        cur = cur->_parent;
    }
    return r;
}


template<typename TreeItem>
RedBlackTreeNode<TreeItem>::RedBlackTreeNode(TreeItem item, RedBlackTreeNode<TreeItem> *left,
                                             RedBlackTreeNode<TreeItem> *right, RedBlackTreeNode<TreeItem> *parent) :
        _value(item),
        _color(RED),
        _left(left),
        _right(right),
        _parent(parent)
{
    _size = 0;
}

template<typename TreeItem>
TreeItem RedBlackTreeNode<TreeItem>::value() {
    return _value;
}

template<typename TreeItem>
Node<TreeItem> *RedBlackTreeNode<TreeItem>::next() {
    if (_right != nullptr){
        RedBlackTreeNode<TreeItem> * cur = _right;
        while (cur->_left != nullptr)
            cur = cur->_left;
        return cur;
    }
    RedBlackTreeNode<TreeItem> * cur = this;
    while (cur->_parent != nullptr && cur->_parent->_right == cur)
        cur = cur->_parent;
    return cur->_parent;
}


#endif //ALGORITHMS_REDBLACKTREE_HPP
