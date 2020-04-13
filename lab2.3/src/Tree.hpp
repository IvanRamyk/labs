//
// Created by ivan on 08.04.20.
//

#ifndef ALGORITHMS_TREE_HPP
#define ALGORITHMS_TREE_HPP

template <typename TreeItem>
class TreeIterator;

template <typename TreeItem>
class Node {
public:
    virtual Node<TreeItem> *  next() {}

    virtual TreeItem  value() {}
};

template <typename TreeItem>
class Tree {
public:
    virtual TreeIterator<TreeItem> begin() {}
    virtual TreeIterator<TreeItem> end() {}
};

template <typename TreeItem>
class TreeIterator {
private:
    Node <TreeItem> * node;
public:
    TreeIterator(Node<TreeItem> * _node){
        node = _node;
    }
    bool operator ()(){
        return node != nullptr;
    }
    TreeItem operator *(){
        return node->value();
    }
    void operator ++(){
        node = node->next();
    }
    bool operator !=(TreeIterator<TreeItem> another){
        return this->node != another.node;
    }
};

#endif //ALGORITHMS_TREE_HPP
