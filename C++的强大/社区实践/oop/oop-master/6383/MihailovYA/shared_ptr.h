namespace stepik
{
template <typename T>
class shared_ptr
{
template <typename A>
friend class shared_ptr;
public:
explicit shared_ptr(T *ptr = 0): ptr(ptr), count(new unsigned(1))
{
}

~shared_ptr()
{
decref();
}

shared_ptr(const shared_ptr& other): ptr(other.ptr), count(other.count)
{
incref();
}

template <typename A> 
shared_ptr(const shared_ptr<A>& other): ptr(other.ptr), count(other.count)
{
incref();
} 

shared_ptr& operator=(const shared_ptr& other)
{
if (ptr == other.ptr) return *this;
decref();
ptr = other.ptr;
count = other.count;
incref();
return *this;
}

template <typename A>
shared_ptr& operator=(const shared_ptr<A>& other)
{
if (ptr == other.ptr) return *this;
decref();
ptr = other.ptr;
count = other.count;
incref();
return *this;
}

explicit operator bool() const
{
return ptr != nullptr;
}

T* get() const
{
return ptr;
}

long use_count() const
{
if (ptr == nullptr) return 0;
else return *count;
}

T& operator*() const
{
return *ptr;
}

T* operator->() const
{
return ptr;
}
template <typename A> 
bool operator==(const shared_ptr<A>& o) const { return ptr == o.ptr; }
template <typename A> 
bool operator!=(const shared_ptr<A>& o) const { return ptr != o.ptr; }
template <typename A>
bool operator<(const shared_ptr<A>& o) const { return ptr < o.ptr; } 


void swap(shared_ptr& x) noexcept
{
std::swap(this->ptr, x.ptr);
std::swap(this->count, x.count);
}

void reset(T *ptr = 0)
{
shared_ptr temp(ptr);
swap(temp);
}

private:
T* ptr;
unsigned* count;
void decref() {
if (--(*count) == 0) {
delete ptr; 
delete count; 
}
} 
void incref() { ++(*count); }
}; 
} // namespace s
