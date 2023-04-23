#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace stepik {
    template <class Type>
    struct node {
        Type value;
        node* next;
        node* prev;

        node(const Type& value, node<Type>* next, node<Type>* prev)
        : value(value), next(next), prev(prev) {
        }
    };



    template <class Type>
    class list;



    template <class Type>
    class list_iterator {
    public:
        typedef ptrdiff_t difference_type;
        typedef Type value_type;
        typedef Type* pointer;
        typedef Type& reference;
        typedef size_t size_type;
        typedef std::forward_iterator_tag iterator_category;

        list_iterator() : m_node(nullptr) {
        }

        list_iterator(const list_iterator& other) : m_node(other.m_node) {
        }

        list_iterator& operator = (const list_iterator& other) {
            m_node = other.m_node;
            return *this;
        }

        bool operator == (const list_iterator& other) const {
            return m_node == other.m_node;
        }

        bool operator != (const list_iterator& other) const {
            return m_node != other.m_node;
        }

        reference operator * () {
            return m_node->value;
        }

        pointer operator -> () {
            return &(m_node->value);
        }

        list_iterator& operator ++ () {
            m_node = m_node->next;
            return *this;
        }

        list_iterator operator ++ (int) {
            list_iterator temp(*this);
            ++(*this);
            return temp;
        }

    private:
        friend class list<Type>;

        list_iterator(node<Type>* p) : m_node(p) {
        }

        node<Type>* m_node;
    };



    template <class Type>
    class list {
    public:
        typedef Type value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef list_iterator<Type> iterator;


        // Constructors and destructor

        list() : m_head(nullptr), m_tail(nullptr) {
        }
      
        list(const list& other) : list() {
            for (node<Type> *ptr = other.m_head; ptr != nullptr; ptr = ptr->next)
                push_back(ptr->value);
        }

        list(list&& other) : list() {
            std::swap(m_head, other.m_head);
            std::swap(m_tail, other.m_tail);
        }

        ~list() {
            clear();
        }


        // Methods and operators

        list& operator=(const list& other) {
            if(this != &other){
                clear();
                for (node<Type> *ptr = other.m_head; ptr != nullptr; ptr = ptr->next)
                    push_back(ptr->value);
            }
            return *this;
        }

        list::iterator begin() {
            return iterator(m_head);
        }

        list::iterator end() {
            return iterator();
        }

        void push_back(const value_type& value) {
            if(m_head == nullptr) {
                m_head = new node<Type>(value, nullptr, nullptr);
                m_tail = m_head;
            } else {
                m_tail->next = new node<Type>(value, nullptr, m_tail);
                m_tail = m_tail->next;
            }
        }

        void push_front(const value_type& value) {
            if(m_head == nullptr) {
                m_head = new node<Type>(value, nullptr, nullptr);
                m_tail = m_head;
            } else {
                m_head->prev = new node<Type>(value, m_head, nullptr);
                m_head = m_head->prev;
            }
        }

        iterator insert(iterator pos, const Type& value) {
            if (pos.m_node == nullptr) {
                push_back(value);
                return iterator(m_tail);
            }
            if (pos.m_node->prev == nullptr) {
                push_front(value);
                return iterator(m_head);
            }
            node<Type>* temp = new node<Type>(value, pos.m_node, pos.m_node->prev);
            pos.m_node->prev->next = temp;
            pos.m_node->prev = temp;
            return iterator(temp);
        }

        iterator erase(iterator pos) {
            if (pos.m_node == nullptr)
                return pos;
            if (pos.m_node->next == nullptr) {
                pop_back();
                return nullptr;
            }
            if (pos.m_node->prev == nullptr) {
                pop_front();
                return iterator(m_head);
            }
            node<Type>* temp = pos.m_node->next;
            pos.m_node->prev->next = temp;
            temp->prev = pos.m_node->prev;
            delete pos.m_node;
            return temp;
        }

        reference front() {
            return m_head->value;
        }

        const_reference front() const {
            return m_head->value;
        }

        reference back() {
            return m_tail->value;
        }

        const_reference back() const {
            return m_tail->value;
        }

        void pop_front() {
            if(!empty()){
                if (m_head == m_tail){
                    delete m_head;
                    m_head = nullptr;
                    m_tail = nullptr;
                } else {
                    m_head = m_head->next;
                    delete m_head->prev;
                    m_head->prev = nullptr;
                }
            }
        }

        void pop_back() {
            if(!empty()){
                if (m_head == m_tail){
                    delete m_head;
                    m_head = nullptr;
                    m_tail = nullptr;
                } else {
                    m_tail = m_tail->prev;
                    delete m_tail->next;
                    m_tail->next = nullptr;
                }
              }
        }

        void clear() {
            while (!empty())
                pop_front();
        }

        bool empty() const {
            return m_tail == nullptr;
        }

        size_t size() const {
            size_t result = 0;
            node<Type> *ptr = m_head;
            while( ptr != nullptr) {
                result++;
                ptr = ptr->next;
            }
            return result;
        }

    private:

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}