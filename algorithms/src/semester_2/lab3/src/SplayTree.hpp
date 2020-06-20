//
// Created by ivan on 08.04.20.
//

#ifndef ALGORITHMS_SPLAYTREE_HPP
#define ALGORITHMS_SPLAYTREE_HPP

#include <vector>
#include "Tree.hpp"

template <typename TreeItem>
class SplayTree;

template <typename TreeItem>
class SplayTreeNode: public Node<TreeItem>{
private:
    TreeItem _value;
    SplayTreeNode<TreeItem> * _left;
    SplayTreeNode<TreeItem> * _right;
    SplayTreeNode<TreeItem> * _parent;
public:
    explicit SplayTreeNode<TreeItem> (
            TreeItem item,
            SplayTreeNode<TreeItem> * left = nullptr,
            SplayTreeNode<TreeItem> * right = nullptr,
            SplayTreeNode<TreeItem> * parent = nullptr);

    TreeItem value();

    Node<TreeItem> * next();

    friend class SplayTree<TreeItem>;
};

template <typename TreeItem>
class SplayTree: public Tree<TreeItem> {
private:
    SplayTreeNode <TreeItem> * _root;

    void _print(SplayTreeNode<TreeItem> * node, std::vector<std::pair<TreeItem, TreeItem>> &events);

    int _height(SplayTreeNode<TreeItem> * node);

    void _rotate(SplayTreeNode<TreeItem> * node);

    SplayTreeNode<TreeItem> * _splay(SplayTreeNode<TreeItem> * node);

    SplayTreeNode<TreeItem> * _search(SplayTreeNode<TreeItem> * node, TreeItem item);

    std::pair<SplayTreeNode<TreeItem> * , SplayTreeNode<TreeItem> * > _split(TreeItem key);

    SplayTreeNode <TreeItem> * _merge(SplayTreeNode<TreeItem> * first, SplayTreeNode<TreeItem> * second);

public:
    TreeIterator<TreeItem> begin();

    TreeIterator<TreeItem> end();

    explicit SplayTree(SplayTreeNode <TreeItem> * root = nullptr);

    void insert(TreeItem item);

    SplayTreeNode <TreeItem> * search(TreeItem item);

    void remove(SplayTreeNode <TreeItem> * z);

    std::vector<std::pair<TreeItem, TreeItem>> print();

    int height();
};


template<typename TreeItem>
void SplayTree<TreeItem>::_print(SplayTreeNode<TreeItem> *node, std::vector<std::pair<TreeItem, TreeItem>> &events) {
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
SplayTree<TreeItem>::SplayTree(SplayTreeNode <TreeItem> * root) {
    _root = root;
}

template<typename TreeItem>
int SplayTree<TreeItem>::_height(SplayTreeNode<TreeItem> *node) {
    if (node == nullptr)
        return 0;
    return std::max(_height(node->_left), _height(node->_right)) + 1;
}

template<typename TreeItem>
int SplayTree<TreeItem>::height() {
    return _height(_root);
}

template<typename TreeItem>
SplayTreeNode<TreeItem>::SplayTreeNode(TreeItem item, SplayTreeNode<TreeItem> *left,
                                       SplayTreeNode<TreeItem> *right, SplayTreeNode<TreeItem> *parent) :
        _value(item),
        _left(left),
        _right(right),
        _parent(parent)
{}

template<typename TreeItem>
TreeItem SplayTreeNode<TreeItem>::value() {
    return _value;
}

template<typename TreeItem>
Node<TreeItem> *SplayTreeNode<TreeItem>::next() {
    if (_right != nullptr){
        SplayTreeNode<TreeItem> * cur = _right;
        while (cur->_left != nullptr)
            cur = cur->_left;
        return cur;
    }
    SplayTreeNode<TreeItem> * cur = this;
    while (cur->_parent != nullptr && cur->_parent->_right == cur)
        cur = cur->_parent;
    return cur->_parent;
}

template<typename TreeItem>
std::vector<std::pair<TreeItem, TreeItem>> SplayTree<TreeItem>::print() {
    std::vector<std::pair<TreeItem, TreeItem>> events;
    _print(_root, events);
    return events;
}

template<typename TreeItem>
SplayTreeNode<TreeItem> * SplayTree<TreeItem>::search(TreeItem item) {
    _root = _search(_root, item);
    if (_root != nullptr && _root->value() == item)
        return _root;
    return nullptr;
}

template<typename TreeItem>
void SplayTree<TreeItem>::insert(TreeItem item) {
    std::pair<SplayTreeNode<TreeItem> * , SplayTreeNode<TreeItem> * > split_res = _split(item);
    _root = new SplayTreeNode<TreeItem>(item, split_res.first, split_res.second, nullptr);
    if (_root->_left != nullptr) {
        _root->_left->_parent = _root;
    }
    if (_root->_right != nullptr) {
         _root->_right->_parent = _root;
    }
}

template<typename TreeItem>
void SplayTree<TreeItem>::remove(SplayTreeNode<TreeItem> * z) {
    if (z == nullptr)
        return;
    _root = _search(_root, z->value());
    SplayTreeNode <TreeItem> * left = _root->_left;
    SplayTreeNode <TreeItem> * right = _root->_right;
    if (left != nullptr)
        left->_parent = nullptr;
    if (right != nullptr)
        right->_parent = nullptr;
    _root = _merge(left, right);
}

template<typename TreeItem>
SplayTreeNode<TreeItem> *SplayTree<TreeItem>::_merge(SplayTreeNode<TreeItem> *first, SplayTreeNode<TreeItem> *second) {
    if (first == nullptr)
        return second;
    if (second == nullptr)
        return first;
    TreeItem item = first->value();
    second = _search(second, item);
    first->_parent = second;
    second->_left = first;
    return second;
}

template<typename TreeItem>
void SplayTree<TreeItem>::_rotate(SplayTreeNode<TreeItem> *node) {
    if (node != nullptr && node->_parent != nullptr) {
        if (node->_parent->_left == node) {
            SplayTreeNode<TreeItem> *parent = node->_parent;
            //SplayTreeNode<TreeItem> * left = node->left;
            SplayTreeNode<TreeItem> *middle = node->_right;
            SplayTreeNode<TreeItem> *right = node->_parent->_right;
            SplayTreeNode<TreeItem> *grandparent = node->_parent->_parent;
            node->_right = parent;
            node->_parent = grandparent;
            if (grandparent != nullptr) {
                if (grandparent->_left == parent)
                    grandparent->_left = node;
                else
                    grandparent->_right = node;
            }
            parent->_parent = node;
            parent->_left = middle;
            if (middle != nullptr)
                middle->_parent = parent;
        }
        else {
            SplayTreeNode<TreeItem> *parent = node->_parent;
            SplayTreeNode<TreeItem> * left = parent->_left;
            SplayTreeNode<TreeItem> *middle = node->_left;
            SplayTreeNode<TreeItem> *right = node->_right;
            SplayTreeNode<TreeItem> *grandparent = node->_parent->_parent;
            node->_left = parent;
            node->_parent = grandparent;
            if (grandparent != nullptr) {
                if (grandparent->_left == parent)
                    grandparent->_left = node;
                else
                    grandparent->_right = node;
            }
            parent->_parent = node;
            parent->_right = middle;
            if (middle != nullptr)
                middle->_parent = parent;
        }
    }
}

template<typename TreeItem>
SplayTreeNode<TreeItem> *SplayTree<TreeItem>::_splay(SplayTreeNode<TreeItem> *node) {
    if (node == nullptr || node->_parent == nullptr)
        return node;
    SplayTreeNode<TreeItem> * parent = node->_parent;
    SplayTreeNode<TreeItem> * grandparent = parent->_parent;
    if (grandparent == nullptr){
        _rotate(node);
        return node;
    }
    bool zigzig = (grandparent->_left == parent) == (parent->_left == node);
    if (zigzig){
        _rotate(parent);
        _rotate(node);
    }
    else  {
        _rotate(node);
        _rotate(node);
    }
    return _splay(node);
}

template<typename TreeItem>
SplayTreeNode<TreeItem> *SplayTree<TreeItem>::_search(SplayTreeNode<TreeItem> *node, TreeItem item) {
    if (node == nullptr)
        return nullptr;
    if (item == node->value())
        return _splay(node);
    if (item < node->value() && node->_left != nullptr)
        return _search(node->_left, item);
    if (node->value() < item && node->_right != nullptr)
        return _search(node->_right, item);
    return _splay(node);
}

template<typename TreeItem>
std::pair<SplayTreeNode<TreeItem> *, SplayTreeNode<TreeItem> *> SplayTree<TreeItem>::_split(TreeItem key) {
    if (_root == nullptr)
        return {nullptr, nullptr};
    SplayTreeNode<TreeItem> * temp = _search(_root, key);
    if (temp->value() == key)
        return {temp->_left, temp->_right};
    if (temp->value() < key) {
        SplayTreeNode<TreeItem> * right = temp->_right;
        temp->_right = nullptr;
        return {temp, right};
    }
    SplayTreeNode<TreeItem> * left = temp->_left;
    temp->_left = nullptr;
    return {left, temp};
}

template<typename TreeItem>
TreeIterator<TreeItem> SplayTree<TreeItem>::begin() {
    if (_root == nullptr)
        return TreeIterator<TreeItem>(nullptr);
    SplayTreeNode<TreeItem> * cur = _root;
    while (cur->_left != nullptr)
        cur = cur->_left;
    return TreeIterator<TreeItem>(cur);
}

template<typename TreeItem>
TreeIterator<TreeItem> SplayTree<TreeItem>::end() {
    return TreeIterator<TreeItem>(nullptr);
}


#endif //ALGORITHMS_SPLAYTREE_HPP
