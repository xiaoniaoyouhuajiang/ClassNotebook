//
// Created by Максим Бачинский on 16.05.17.
//

#ifndef INC_5_LIST_H
#define INC_5_LIST_H

#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace stepik {
    template<class Type>
    struct node {
        Type value;
        node *next;
        node *prev;

        node(const Type &value, node<Type> *next, node<Type> *prev)
                : value(value), next(next), prev(prev) {
        }
    };

    template<class Type>
    class list; //forward declaration

    template<class Type>
    class list_iterator {
    public:
        typedef ptrdiff_t difference_type;
        typedef Type value_type;
        typedef Type *pointer;
        typedef Type &reference;
        typedef size_t size_type;
        typedef std::forward_iterator_tag iterator_category;

        list_iterator()
                : m_node(NULL) {
        }

        list_iterator(const list_iterator &other)
                : m_node(other.m_node) {
        }

        list_iterator &operator=(const list_iterator &other) {
            m_node = other.m_node;
        }

        bool operator==(const list_iterator &other) const {
            return this->m_node == other.m_node;
        }

        bool operator!=(const list_iterator &other) const {
            return !operator==(other);
        }

        reference operator*() {
            return m_node->value;
        }

        pointer operator->() {
            Type *t = new Type(m_node->value);
            return t;
        }

        list_iterator &operator++() {
            m_node = m_node->next;

            return *this;

        }

        list_iterator operator++(int) {
            list_iterator temp = *this;
            ++*this;
            return temp;
        }

    private:
        friend class list<Type>;

        list_iterator(node<Type> *p)
                : m_node(p) {
        }

        node<Type> *m_node;
    };

    template<class Type>
    class list {
    public:
        typedef Type value_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef list_iterator<Type> iterator;

        list()
                : m_head(nullptr), m_tail(nullptr) {
        }

        ~list() {
            delete_all();
        }

        list::iterator begin() const{
            return iterator(m_head);
        }

        list::iterator end() const{
            return iterator();
        }

        list(const list &other) : list() {
            node<value_type> *tail = other.m_head;
            while (tail != NULL) {
                this->push_back(tail->value);
                tail = tail->next;
            }
        }


        iterator insert(iterator pos, const Type &value) {
            if (pos.m_node == NULL) {
                push_back(value);
                return iterator(m_tail);
            } else if (pos.m_node->prev == NULL) {
                push_front(value);
                return begin();
            }  else {
                node<value_type> *n = new node<value_type>(value, pos.m_node, pos.m_node->prev);
                pos.m_node->prev->next = n;
                pos.m_node->prev = n;
                return iterator(n);
            }


        }

        iterator erase(iterator pos) {
            if (pos.m_node->prev == NULL) {
                pop_front();
                return begin();
            } else if (pos.m_node->next == NULL) {
                pop_back();
                return iterator(m_tail);
            } else {
                pos.m_node->next->prev = pos.m_node->prev;
                pos.m_node->prev->next = pos.m_node->next;
                node<value_type> *n = pos.m_node;
                iterator i(pos.m_node->next);
                delete n;
                return i;
            }


        }

        list(list &&other) : m_head(other.m_head), m_tail(other.m_tail) {
            other.m_head = NULL;
            other.m_tail = NULL;
        }

        list &operator=(const list &other) {
            if (this != &other) {
                delete_all();
                node<value_type> *tail = other.m_head;
                while (tail != NULL) {
                    this->push_back(tail->value);
                    tail = tail->next;
                }
            }
            return *this;
        }

        void push_back(const value_type &value) {
            if (empty()) {
                add_first(value);
            } else {
                node<value_type> *n = new node<value_type>(value, nullptr, this->m_tail);
                m_tail->next = n;
                m_tail = n;
            }

        }

        void push_front(const value_type &value) {
            if (empty()) {
                add_first(value);
            } else {
                node<value_type> *n = new node<value_type>(value, this->m_head, nullptr);
                m_head->prev = n;
                m_head = n;
            }
        }

        reference front() {
            return m_head->value;
        }

        const_reference front() const {
            node<value_type> *node = m_head;
            return &node->value;
        }

        reference back() {
            return m_tail->value;
        }

        const_reference back() const {
            node<value_type> *node = m_tail;
            return &node->value;
        }

        void pop_front() {
            if (size() == 1) {
                delete_last();
            } else if (!empty()) {
                node<value_type> *newHead = m_head->next;
                newHead->prev = nullptr;
                node<value_type> *old = m_head;
                m_head = newHead;
                delete old;
            }
        }

        void pop_back() {
            if (size() == 1) {
                delete_last();
            } else if (!empty()) {
                node<value_type> *newTail = m_tail->prev;
                newTail->next = nullptr;
                node<value_type> *old = m_tail;
                m_tail = newTail;
                delete old;

            }
        }

        void clear() {
            delete_all();
        }

        bool empty() const {
            return m_head == 0;
        }

        size_t size() const {
            size_t s = 0;
            node<value_type> *n = m_head;
            while (n != NULL) {
                s++;
                n = n->next;
            }
            return s;

        }

    private:
        //your private functions

        void add_first(const value_type &value) {
            node<value_type> *n = new node<value_type>(value, nullptr, nullptr);
            m_tail = n;
            m_head = n;
        }

        void delete_last() {
            node<value_type> *n = m_head;
            m_head = NULL;
            m_tail = NULL;
            delete n;
        }

        void delete_all() {
            if (!empty()) {
                while (m_head != m_tail) {
                    node<value_type> *newHead = m_head->next;
                    newHead->prev = nullptr;
                    delete m_head;
                    m_head = newHead;
                }
                delete m_tail;
                m_head = NULL;
                m_tail = NULL;
            }
        }

        node<Type> *m_head;
        node<Type> *m_tail;
    };

}// namespace stepik

#endif //INC_5_LIST_H
