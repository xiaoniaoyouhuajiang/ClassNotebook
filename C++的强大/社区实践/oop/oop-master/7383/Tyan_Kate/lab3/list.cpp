#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace stepik
{
    template <class Type>
    struct node
    {
        Type value;
        node* next;
        node* prev;
        
        node(const Type& value, node<Type>* next, node<Type>* prev)
        : value(value), next(next), prev(prev)
        {
        }
    };
    
    template <class Type>
    class list;
    
    template <class Type>
    class list_iterator
    {
    public:
        typedef ptrdiff_t difference_type;
        typedef Type value_type;
        typedef Type* pointer;
        typedef Type& reference;
        typedef size_t size_type;
        typedef std::forward_iterator_tag iterator_category;
        
        list_iterator()
        : m_node(NULL)
        {
        }
        
        list_iterator(const list_iterator& other)
        : m_node(other.m_node)
        {
        }
        
        list_iterator& operator = (const list_iterator& other)
        {
            if(this != &other){
                m_node = other.m_node;
            }
            return *this;// implement this
        }
        
        bool operator == (const list_iterator& other) const
        {
            return m_node == other.m_node;// implement this
        }
        
        bool operator != (const list_iterator& other) const
        {
            return m_node != other.m_node;// implement this
        }
        
        reference operator * ()
        {
            return m_node -> value;// implement this
        }
        
        pointer operator -> ()
        {
            return &(m_node -> value);// implement this
        }
        
        list_iterator& operator ++ ()
        {
            m_node = m_node -> next;
            return *this;// implement this
        }
        
        list_iterator operator ++ (int)
        {
            list_iterator tmp = *m_node;
            m_node = m_node -> next;
            return tmp;// implement this
        }
        
    private:
        friend class list<Type>;
        
        list_iterator(node<Type>* p)
        : m_node(p)
        {
        }
        
        node<Type>* m_node;
    };
    
    template <class Type>
    class list
    {
    public:
        typedef Type value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef list_iterator<Type> iterator;
        
        list()
        : m_head(nullptr), m_tail(nullptr)
        {
        }
        
        ~list()
        {
            while(m_head){
                if(m_head == m_tail){
                    delete m_head;
                    m_head = nullptr;
                    m_tail = nullptr;
                    return;
                }
                node<Type>* ptr = m_head -> next;
                delete m_head;
                m_head = ptr;
                m_head -> prev = nullptr;
            }
            m_head = nullptr;
            m_tail = nullptr;// implement this
        }
        
        list(const list& other) : m_head(nullptr), m_tail(nullptr)
        {
            if(other.m_head == nullptr)
                return;
            node<Type>* ptr = other.m_head;
            while(ptr){
                push_back(ptr -> value);
                ptr = ptr -> next;
            }// implement this
        }
        
        list(list&& other) : m_head(other.m_head), m_tail(other.m_tail)
        {
            other.m_head = nullptr;
            other.m_tail = nullptr;// implement this
        }
        
        list& operator= (const list& other)
        {
            if(m_head == other.m_head)
                return *this;
            while(m_head){
                if(m_head == m_tail){
                    delete m_head;
                    m_head = nullptr;
                    m_tail = nullptr;
                }else{
                    node<Type>* ptr = m_head -> next;
                    delete m_head;
                    m_head = ptr;
                    m_head -> prev = nullptr;
                }
                m_head = nullptr;
                m_tail = nullptr;
            }
            node<Type>* ptr = other.m_head;
            while(ptr){
                push_back(ptr -> value);
                ptr = ptr -> next;
            }
            return *this;
            // implement this
        }
        
        list::iterator begin()
        {
            return iterator(m_head);
        }
        
        list::iterator end()
        {
            return iterator();
        }
        
        void push_back(const value_type& value)
        {
            if(empty()){
                m_head = new node<Type> (value, nullptr, nullptr);
                m_tail = m_head;
                return;
            }
            m_tail -> next = new node<Type> (value, nullptr, m_tail);
            m_tail = m_tail -> next;
            // implement this
        }
        
        void push_front(const value_type& value)
        {
            if(empty()){
                m_head = new node<Type> (value, nullptr, nullptr);
                m_tail = m_head;
                return;
            }
            m_head -> prev = new node<Type> (value, m_head, nullptr);
            m_head = m_head -> prev;            // implement this
        }
        
        iterator insert(iterator pos, const Type& value)
        {
            node<Type>* new_el;
            if(pos.m_node == nullptr){
                push_back(value);
                return iterator(m_tail);
            }
            if(pos == begin()){
                new_el = new node<Type> (value, m_head, nullptr);
                m_head -> prev = new_el;
                m_head = new_el;
                return begin();
            }
            new_el = new node<Type> (value, pos.m_node, pos.m_node -> prev);
            pos.m_node -> prev -> next = new_el;
            pos.m_node -> prev = new_el;
            return iterator(new_el);// implement this
        }
        
        iterator erase(iterator pos)
        {
            if(pos.m_node == nullptr){
                return nullptr;
            }
            if(pos == begin()){
                m_head = m_head -> next;
                delete m_head -> prev;
                m_head -> prev = nullptr;
                return begin();
            }
            if(pos.m_node == m_tail){
                m_tail = m_tail -> prev;
                delete m_tail -> next;
                m_tail -> next = nullptr;
                return iterator(m_tail);
            }
            node<Type>* tmp = pos.m_node -> next;
            pos.m_node -> next -> prev = pos.m_node -> prev;
            pos.m_node -> prev -> next = pos.m_node -> next;
            delete pos.m_node;
            return iterator(tmp);
            // implement this
        }
        
        reference front()
        {
            return m_head -> value;// implement this
        }
        
        const_reference front() const
        {
            return m_head -> value;// implement this
        }
        
        reference back()
        {
            return m_tail -> value;// implement this
        }
        
        const_reference back() const
        {
            return m_tail -> value;// implement this
        }
        
        void pop_front()
        {
            if(empty())
                return;
            if(size() == 1){
                delete m_head;
                m_head = nullptr;
                m_tail = nullptr;
                return;
            }
            node<Type>* ptr = m_head -> next;
            delete m_head;
            m_head = ptr;
            m_head -> prev = nullptr;
            // implement this
        }
        
        void pop_back()
        {
            if(empty())
                return;
            if(size() == 1){
                delete m_head;
                m_head = nullptr;
                m_tail = nullptr;
                return;
            }
            node<Type>* ptr = m_tail -> prev;
            delete m_tail;
            m_tail = ptr;
            m_tail -> next = nullptr;// implement this
        }
        
        void clear()
        {
            while(empty())
                pop_front();
            m_head = nullptr;
            m_tail = nullptr;// implement this
        }
        
        bool empty() const
        {
            return m_head == nullptr;// implement this
        }
        
        size_t size() const
        {
            size_t i=0;
            node<Type>* ptr = m_head;
            while(ptr){
                ++i;
                ptr = ptr -> next;
            }
            return i;
            // implement this
        }
        
    private:
        //your private functions
        
        node<Type>* m_head;
        node<Type>* m_tail;
    };
    
}// namespace stepik
