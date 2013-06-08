
/* 
 * File:   list.h
 * Author: georgeee
 *
 * Created on 7 Апрель 2013 г., 15:40
 */

#include <algorithm>
#include <utility>

#ifndef LIST_H
#define	LIST_H

template<typename T>
class List {
private:

    class Node {
        friend class List;
        friend class Iterator;
    private:

        Node(T value)
                : next_node(nullptr)
                , prev_node(nullptr)
                , value(value)
        {}
                
        Node* next_node;
        Node* prev_node;
        T value;
    };
    Node * fake_node;
    int _size;
public:

    class Iterator {
        friend class List;
    private:
        Node * node_pointer;
    public:

        Iterator(Node * nodePtr) {
            this->node_pointer = nodePtr;
        }

        Iterator(const Iterator& orig) {
            this->node_pointer = orig.node_pointer;
        }

        T& operator*() const {
            return this->node_pointer->value;
        }

        Iterator& operator++() {
            node_pointer = node_pointer->next_node;
            return (*this);
        }

        Iterator operator++(int) {
            Iterator t = *this;
            ++(*this);
            return t;
        }

        Iterator& operator--() {
            node_pointer = node_pointer->prev_node;
            return (*this);
        }

        Iterator operator--(int) {
            Iterator a = *this;
            --(*this);
            return a;
        }

        bool operator==(const Iterator & x) const {
            return node_pointer == x.node_pointer;
        }

        bool operator!=(const Iterator & x) const {
            return !(*this == x);
        }
    };

    class ConstIterator {
        friend class List;
    private:
        const Node * node_pointer;
    public:

        ConstIterator(Node * nodePtr) {
            this->node_pointer = nodePtr;
        }

        ConstIterator(const ConstIterator& orig) {
            this->node_pointer = orig.node_pointer;
        }

        const T& operator*() const {
            return this->node_pointer->value;
        }

        ConstIterator& operator++() {
            node_pointer = node_pointer->next_node;
            return (*this);
        }

        ConstIterator operator++(int) {
            ConstIterator a = *this;
            ++(*this);
            return a;
        }

        ConstIterator& operator--() {
            node_pointer = node_pointer->prev_node;
            return (*this);
        }

        ConstIterator operator--(int) {
            ConstIterator a = *this;
            --(*this);
            return a;
        }

        bool operator==(const ConstIterator & x) const {
            return node_pointer == x.node_pointer;
        }

        bool operator!=(const ConstIterator & x) const {
            return !(*this == x);
        }
    };

    class ListException {
    private:
        const char * msg;
    public:

        ListException(const char * msg) {
            this->msg = msg;
        }

        const char * get_message() const {
            return this->msg;
        }
    };
private:

    void init() {
        _size = 0;
        fake_node = new Node(0);
        fake_node->prev_node = fake_node->next_node = fake_node;
    }
public:

    List() {
        init();
    }

    List(const List & l) {
        init();
        for (List::ConstIterator it = l.cbegin(); it != l.cend(); ++it) {
            push_back(*it);
        }
    }

    int size() const {
        return _size;
    }

    bool is_empty() const {
        return size() == 0;
    }
private:

    void throw_empty_exception() const {
        if (is_empty()) throw ListException("list is empty");
    }

    void erase_node(Node * n) {
        n->next_node->prev_node = n->prev_node;
        n->prev_node->next_node = n->next_node;
        delete n;
        _size--;
    }

    void insert_after(Node * _node, Node * insertion) {
        insertion->next_node = _node->next_node;
        insertion->prev_node = _node;
        _node->next_node->prev_node = insertion;
        _node->next_node = insertion;
        _size++;
    }

public:

    void push_back(T value) {
        insert_after(fake_node->prev_node, new Node(value));
    }

    T pop_back() {
        throw_empty_exception();
        Node * n = fake_node->prev_node;
        T value = n->value;
        erase_node(n);
        return value;
    }

    T& back() {
        throw_empty_exception();
        return fake_node->prev_node->value;
    }

    T const& back() const {
        throw_empty_exception();
        return fake_node->prev_node->value;
    }

    void push_front(T value) {
        insert_after(fake_node, new Node(value));
    }

    T pop_front() {
        throw_empty_exception();
        Node * n = fake_node->next_node;
        T value = n->value;
        erase_node(n);
        return value;
    }

    T& front() {
        throw_empty_exception();
        return fake_node->next_node->value;
    }

    T const& front() const {
        throw_empty_exception();
        return fake_node->next_node->value;
    }

    Iterator begin() {
        return Iterator(fake_node->next_node);
    }

    Iterator end() {
        return Iterator(fake_node);
    }

    ConstIterator cbegin() const {
        return ConstIterator(fake_node->next_node);
    }

    ConstIterator cend() const {
        return ConstIterator(fake_node);
    }

    Iterator erase(Iterator it) {
        Node * node_pointer = it.node_pointer;
        ++it;
        erase_node(node_pointer);
        return it;
    }

    Iterator insert(Iterator it, T const& value) {
        Node * node_pointer = it.node_pointer->prev_node;
        insert_after(node_pointer, new Node(value));
        return Iterator(node_pointer->next_node);
    }

    List& operator=(List l) {
        std::swap(l.fake_node, fake_node);
        std::swap(l._size, _size);
        return *this;
    }

    ~List() {
        for (Iterator it = begin(); it != end(); it = erase(it));
        delete fake_node;
    }

};


#endif	/* LIST_H */

