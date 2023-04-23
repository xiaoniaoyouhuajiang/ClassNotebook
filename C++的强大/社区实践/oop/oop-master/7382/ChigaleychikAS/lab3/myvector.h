        #include <assert.h>
        #include <utility> // std::copy, std::rotate
        #include <cstddef> // size_t
        #include <initializer_list>
        #include <stdexcept>

        namespace stepik
        {
        template <typename Type>
        class vector
        {
        public:
            typedef Type* iterator;
            typedef const Type* const_iterator;

            typedef Type value_type;

            typedef value_type& reference;
            typedef const value_type& const_reference;

            typedef std::ptrdiff_t difference_type;

        
            explicit vector(size_t count = 0) : m_first(new Type[count]),m_last(m_first+count)
            {
            }

            template <typename InputIterator>
            vector(InputIterator first, InputIterator last): vector(last-first)
            {
                std::copy(first,last,m_first);

            }


            vector(std::initializer_list<Type> init): vector(init.size())
            {
            // implement this
            std::copy(init.begin(),init.end(),m_first);
            }

            vector(const vector& other) : vector(other.size())
            {
            // implement this
            //std::cout<<"CPOY CONSTRUCOT"<<std::endl;
            std::copy(other.m_first,other.m_last,m_first);
            }

            vector(vector&& other)
            {
            // std::cout<<"MOVE CONSTRUCOT"<<std::endl;
                this->m_last=std::move(other.m_last);
                this->m_first=std::move(other.m_first);
                other.m_first = nullptr;
                other.m_last = nullptr;/*
                m_first = m_last = nullptr;

                std::swap(m_first, other.m_first);
                std::swap(m_last, other.m_last);*/
            }

            ~vector()
            {
                delete[] m_first;
            }

            //assignment operators
        vector& operator=(const vector& other)
        {
            delete[] this->m_first;
            this->m_first = new Type[other.size()];
            this->m_last = m_first + other.size();
            std::copy(other.begin(),other.end(),this->m_first);
            return *this;
        }

        vector& operator=(vector&& other)
        {
            delete[] this->m_first;
            this->m_last=std::move(other.m_last);
            this->m_first=std::move(other.m_first);            
            other.m_first = nullptr;
            other.m_last = nullptr;
            return *this;
        }

        // assign method
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            *this = vector(first,last);
        }

        // resize methods
    void resize(size_t count)
    {
        if (count==this->size()) return;
        auto tmpfirst = new Type[count];
        if (count< this->size())
        {
            
            std::copy(this->m_first,this->m_first+count,tmpfirst);
        }
        else
        {
            std::copy(m_first,m_last,tmpfirst);
        }
        delete[] m_first;
        this->m_first = tmpfirst;
        this->m_last = tmpfirst + count;
    }



    //erase methods
    iterator erase(const_iterator pos)
    {
        return erase(pos,pos+1);
    }

 
    iterator erase(const_iterator first, const_iterator last)
    // 1 2 3 4
    // 76 77 78 79 80
    //80 76 
    {
        if (this->empty()) return this->m_last;
        auto tmpfirst = new Type[this->size()-(last-first)];

        //std::cout<<this->size()-(last-first+1)<<std::endl;
        auto _first = const_cast<iterator>(first);
        auto _last = const_cast<iterator>(last);

        std::copy(m_first,_first,tmpfirst);
        auto next = std::copy(_last,m_last,tmpfirst+ (_first-m_first));
        m_last = tmpfirst+this->size()-(_last-_first);
        delete[] m_first;
        m_first = tmpfirst;
        return next;
    }
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        return insert(pos,&value,&value+1);
    }


    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        //std::cout<<first<<std::endl<<last<<std::endl;
        auto _pos = const_cast<Type*>(pos);
        auto tmpfirst = new Type[this->size()+last-first]; 
        //std::cout<<this->size()+last-first<<std::endl;

        auto next = std::copy(m_first,_pos,tmpfirst);
        auto tmp = next;
        next = std::copy(first,last,next);
        auto end =  std::copy(_pos,m_last,next);
        delete [] m_first;
        m_first = tmpfirst;
        m_last = end;
        return tmp;
    }
    //1 2 3 4 

    //5 60 61

    //push_back methods
    void push_back(const Type& value)
    {
        insert(this->end(),value);
    }

    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:   
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik