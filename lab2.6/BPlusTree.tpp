//
// Created by darik on 4/10/2020.
//

#include "BPlusTree.hpp"


template<typename T>
shared_ptr<BPlusNode<T> > BPlusTree<T>::_findLeaf(int key) { // according to the principle of binary search tree
    shared_ptr<BPlusNode<T> > cur = this->_root;
    while (!cur->_leaf) {
        for (int i = 0; i <= cur->_key_num; ++i) {
            if (i == cur->_key_num || key < cur->_key[i]) {
                cur = cur->_children[i];
                break;
            }
        }
    }
    return cur;
}

template<typename T>
shared_ptr<T> BPlusTree<T>::search(int key) {
    shared_ptr<BPlusNode<T> > leaf = _findLeaf(key);
    for (int i = 0; i < leaf->_key_num; ++i) {
        if (leaf->_key[i] == key) return leaf->_info[i];
    }
    return nullptr;
}

template<typename T>
bool BPlusTree<T>::insert(int key, shared_ptr<T> value) {
    shared_ptr<BPlusNode<T> > leaf = this->_findLeaf(key);
    if (std::find(leaf->_key.begin(), leaf->_key.end(), key) <
        leaf->_key.end()) // if we already have information with the key,
        // then we can't insert
        return false;

    int pos = 0;
    while (pos < leaf->_key_num && leaf->_key[pos] < key) // find the place in the leaf for new key
        ++pos;

    leaf->_key.insert(leaf->_key.begin() + pos, key);
    leaf->_info.insert(leaf->_info.begin() + pos, value);

    leaf->_key_num++;

    if (leaf->_key_num == 2 * _t) // node can't have 2*t and more keys
        _split(leaf);

    return true;
}

template<typename T>
void BPlusTree<T>::_split(shared_ptr<BPlusNode<T> > node) { // split node to 2 new nodes
    shared_ptr<BPlusNode<T> > new_node = std::make_shared<BPlusNode<T> >();

    new_node->_right_sibling = node->_right_sibling;
    if (node->_right_sibling) node->_right_sibling->_left_sibling = new_node;
    node->_right_sibling = new_node;
    new_node->_left_sibling = node;

    int mid_key = node->_key[this->_t];
    new_node->_key_num = this->_t - 1;
    node->_key_num = this->_t;
    for (int i = 0; i <= new_node->_key_num - 1; ++i) // new_node get last t - 1 keys
    {
        new_node->_key.push_back(node->_key[i + this->_t + 1]);
        if (node->_leaf) new_node->_info.push_back(node->_info[i + this->_t + 1]);
        if (!node->_leaf) // update parents relations
        {
            new_node->_children.push_back(node->_children[i + this->_t + 1]);
            node->_children[i + this->_t + 1]->_parent = new_node;
        }
    }
    if (!node->_leaf) {
        new_node->_children.push_back(node->_children[2 * _t]);
        node->_children[2 * _t]->_parent = new_node;
    }

    if (node->_leaf) {
        ++new_node->_key_num;
        new_node->_leaf = true;

        new_node->_key.insert(new_node->_key.begin(), node->_key[_t]);
        new_node->_info.insert(new_node->_info.begin(), node->_info[_t]);
    }


    node->_key.resize(node->_key_num);
    if (!node->_leaf) node->_children.resize(node->_key_num + 1);
    if (node->_leaf) node->_info.resize(node->_key_num);

    if (node == this->_root) {
        this->_root = std::make_shared<BPlusNode<T> >();
        this->_root->_key.push_back(mid_key);
        this->_root->_children.push_back(node);
        this->_root->_children.push_back(new_node);
        this->_root->_key_num = 1;
        node->_parent = this->_root;
        new_node->_parent = this->_root;
    } else {
        new_node->_parent = node->_parent;
        shared_ptr<BPlusNode<T> > parent = node->_parent;

        int pos = 0;
        while (pos < parent->_key_num && parent->_key[pos] < mid_key)
            ++pos;

        ++parent->_key_num;
        parent->_key.push_back(0);
        parent->_children.push_back(nullptr);
        for (int i = parent->_key_num - 1; i >= pos + 1; --i)
            parent->_key[i] = parent->_key[i - 1];
        for (int i = parent->_key_num; i >= pos + 2; --i)
            parent->_children[i] = parent->_children[i - 1];
        parent->_key[pos] = mid_key;
        parent->_children[pos + 1] = new_node;

        if (parent->_key_num == 2 * _t)
            _split(parent);
    }
}

template<typename T>
bool BPlusTree<T>::remove(int key) {
    shared_ptr<BPlusNode<T> > leaf = _findLeaf(key);
    if (std::find(leaf->_key.begin(), leaf->_key.end(), key) ==
        leaf->_key.end()) // if found leaf doesn't have the key, we have nothing to delete
        return false;
    else
        _removeInNode(leaf, key);
    return true;
}

template<typename T>
int BPlusTree<T>::_getMin(shared_ptr<BPlusNode<T> > node) {
    while (!node->_leaf) {
        node = node->_children[0];
    }
    return node->_key[0];
}

template<typename T>
void BPlusTree<T>::_update(shared_ptr<BPlusNode<T> > node) // update keys in parent nodes
{
    while (node != nullptr) {
        for (int i = 0; i < node->_key_num; ++i) {
            node->_key[i] = _getMin(node->_children[i + 1]);
        }
        node = node->_parent;
    }
}

template<typename T>
void BPlusTree<T>::_removeInNode(shared_ptr<BPlusNode<T> > node, int key) {
    int pos = 0;
    while (pos < node->_key_num && node->_key[pos] < key) // find the position of deleting key
        ++pos;

    node->_key.erase(node->_key.begin() + pos); // delete key from node
    if (node->_leaf) node->_info.erase(node->_info.begin() + pos);
    if (!node->_leaf) node->_children.erase(node->_children.begin() + pos + 1);
    --node->_key_num;

    if (node == _root) { // then reduce height of the tree
        if (node->_key_num == 0) {
            shared_ptr<BPlusNode<T> > child = _root->_children[0];
            _root = child;
            _root->_parent = nullptr;
        }
    } else if (node->_key_num < _t - 1) // keys is less than minimal allowed number of keys
    {
        int pos1 = 0;
        while (pos1 < node->_parent->_key_num &&
               node->_parent->_key[pos1] <= node->_key[0]) // find the position of node in parents children
            ++pos1;

        shared_ptr<BPlusNode<T> > left_sibling;
        shared_ptr<BPlusNode<T> > right_sibling;

        if (pos1 > 0) left_sibling = node->_parent->_children[pos1 - 1];
        if (pos1 < node->_parent->_key_num) right_sibling = node->_parent->_children[pos1 + 1];

        if (!node->_leaf) {
            if (left_sibling != nullptr && left_sibling->_key_num > _t - 1) // then take one key from left sibling
            {
                ++node->_key_num;
                --left_sibling->_key_num;

                node->_key.insert(node->_key.begin(), node->_children[0]->_key[0]);
                node->_children.insert(node->_children.begin(), left_sibling->_children[left_sibling->_key_num + 1]);
                node->_children[0]->_parent = node;

                left_sibling->_key.pop_back();
                left_sibling->_children.pop_back();

                _update(node->_parent);
            } else if (right_sibling != nullptr &&
                       right_sibling->_key_num > _t - 1) // then take one key from right sibling
            {
                ++node->_key_num;
                --right_sibling->_key_num;

                node->_key.push_back(right_sibling->_children[0]->_key[0]);
                node->_children.push_back(right_sibling->_children[0]);
                node->_children[node->_key_num]->_parent = node;

                right_sibling->_key.erase(right_sibling->_key.begin());
                right_sibling->_children.erase(right_sibling->_children.begin());

                _update(node->_parent);
            } else if (left_sibling != nullptr) // then union left sibling and node, update parent node
            {
                left_sibling->_key.push_back(node->_parent->_key[pos1 - 1]);
                left_sibling->_key.insert(left_sibling->_key.end(), node->_key.begin(), node->_key.end());
                left_sibling->_children.insert(left_sibling->_children.end(), node->_children.begin(),
                                               node->_children.end());
                left_sibling->_key_num += node->_key_num + 1;

                for (int i = 0; i <= left_sibling->_key_num; ++i) {
                    left_sibling->_children[i]->_parent = left_sibling;
                }

                _removeInNode(node->_parent, node->_parent->_key[pos1 - 1]);
            } else if (right_sibling != nullptr) // then union node and right sibling
            {
                node->_key.push_back(node->_parent->_key[pos1]);
                node->_key.insert(node->_key.end(), right_sibling->_key.begin(), right_sibling->_key.end());
                node->_children.insert(node->_children.end(), right_sibling->_children.begin(),
                                       right_sibling->_children.end());
                node->_key_num += right_sibling->_key_num + 1;

                for (int i = 0; i <= node->_key_num; ++i) {
                    node->_children[i]->_parent = node;
                }

                _removeInNode(node->_parent, node->_parent->_key[pos1]);
            }
        } else if (node->_leaf) {
            if (left_sibling != nullptr && left_sibling->_key_num > _t - 1) // then take one key from left sibling
            {
                ++node->_key_num;
                --left_sibling->_key_num;
                node->_key.insert(node->_key.begin(), left_sibling->_key[left_sibling->_key_num]);
                node->_info.insert(node->_info.begin(), left_sibling->_info[left_sibling->_key_num]);

                left_sibling->_key.pop_back();
                left_sibling->_info.pop_back();

                _update(left_sibling->_parent);
                if (node->_parent != left_sibling->_parent)
                    _update(node->_parent);
            } else if (right_sibling != nullptr &&
                       right_sibling->_key_num > _t - 1) // then take one key from right sibling
            {
                ++node->_key_num;
                --right_sibling->_key_num;
                node->_key.push_back(right_sibling->_key[0]);
                node->_info.push_back(right_sibling->_info[0]);

                right_sibling->_key.erase(right_sibling->_key.begin());
                right_sibling->_info.erase(right_sibling->_info.begin());

                _update(node->_parent);
                if (node->_parent != right_sibling->_parent)
                    _update(right_sibling->_parent);
            } else if (left_sibling != nullptr) // then union left sibling and node
            {

                left_sibling->_key.insert(left_sibling->_key.end(), node->_key.begin(), node->_key.end());
                left_sibling->_info.insert(left_sibling->_info.end(), node->_info.begin(), node->_info.end());
                left_sibling->_key_num += node->_key_num;

                if (node->_right_sibling)
                    node->_right_sibling->_left_sibling = left_sibling;
                left_sibling->_right_sibling = node->_right_sibling;

                if (left_sibling->_parent == node->_parent) {
                    _removeInNode(node->_parent, node->_parent->_key[pos1 - 1]);
                } else {
                    _removeInNode(node->_parent, node->_parent->_key[0]);
                }
            } else if (right_sibling != nullptr) // then union node and right sibling
            {
                node->_key.insert(node->_key.end(), right_sibling->_key.begin(), right_sibling->_key.end());
                node->_info.insert(node->_info.end(), right_sibling->_info.begin(), right_sibling->_info.end());
                node->_key_num += right_sibling->_key_num;

                if (right_sibling->_right_sibling)
                    right_sibling->_right_sibling->_left_sibling = node;
                node->_right_sibling = right_sibling->_right_sibling;

                if (node->_parent == right_sibling->_parent) {
                    _removeInNode(node->_parent, node->_parent->_key[pos1]);
                } else {
                    _removeInNode(right_sibling->_parent, right_sibling->_parent->_key[0]);
                }
            }
        }
    }
}

//template <class Item>
//BPlusNodeIterator<Item>::BPlusNodeIterator(const shared_ptr<Item> aNode): _node{aNode}, _current(0){}

