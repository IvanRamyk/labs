//
// Created by darik on 4/10/2020.
//

#include <vector>
#include <algorithm>
#include <memory>

using std::shared_ptr;
using std::vector;

#ifndef BPLUS_TREE_HPP
#define BPLUS_TREE_HPP

template<typename T>
class BPlusNode {
public:
    bool _leaf{false};
    int _key_num{0};
    std::vector<int> _key;
    shared_ptr<BPlusNode<T> > _parent;
    shared_ptr<BPlusNode<T> > _left_sibling;
    shared_ptr<BPlusNode<T> > _right_sibling;
    vector<shared_ptr<BPlusNode<T> > > _children;
    vector<shared_ptr<T> > _info;
};

template<typename T>
class BPlusTree {
    class Iterator {
    private:
        shared_ptr<BPlusNode<T>> current_node;
        size_t current_position;
    public:
        Iterator(shared_ptr<BPlusNode<T>> current_node, size_t current_position) :
                current_node{current_node}, current_position{current_position} {}

        Iterator &operator++() {
            ++current_position;
            if (current_position == current_node->_info.size() && current_node->_right_sibling != nullptr) {
                current_node = current_node->_right_sibling;
                current_position = 0;
            }
            return *this;
        }

        T operator*() {
            return *(current_node->_info[current_position]);
        }

        bool operator!=(const Iterator &other) {
            if (this->current_position >= current_node->_info.size() &&
                other.current_position >= other.current_node->_info.size()){
                return false;
            }
            return (this->current_node != other.current_node || this->current_position != other.current_position);
        }

    };

public:
    explicit BPlusTree(int t) : _t{t} {
        _root = std::make_shared<BPlusNode<T> >();
        _root->_leaf = true;
    }

    std::shared_ptr<T> search(int key);

    bool insert(int key, shared_ptr<T> value);

    bool remove(int key);

    Iterator begin() {
        auto answer = _root;
        while (!answer->_leaf) {
            answer = answer->_children[0];
        }
        return Iterator(answer, 0);
    }

    Iterator end() {
        auto answer = _root;
        while (!answer->_leaf) {
            answer = answer->_children[answer->_children.size() - 1];
        }
        return Iterator(answer, answer->_info.size());
    }

private:

    void _removeInNode(shared_ptr<BPlusNode<T> > node, int key);

    void _split(shared_ptr<BPlusNode<T> > node);

    shared_ptr<BPlusNode<T> > _findLeaf(int key);

    int _getMin(shared_ptr<BPlusNode<T> > node);

    void _update(shared_ptr<BPlusNode<T> > node);

    shared_ptr<BPlusNode<T> > _root;
    int _t;
};


#include "BPlusTree.tpp"

#endif //PLUS_TREE_HPP
