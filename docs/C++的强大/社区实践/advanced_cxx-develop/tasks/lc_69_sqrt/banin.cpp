#include <cassert>
#include <algorithm>

// One more bit was necessary to keep overall approcach intact
typedef unsigned long long int lint;

// Inheriting from an iterator considered an ancient practice
class Squares : public std::iterator<
    std::random_access_iterator_tag,
    lint,                    // value_type
    long long int,           // difference_type
    const lint*,             // pointer
    lint>{                   // reference
private:
    lint arg;
public:
    Squares():
        arg(0){
    }
    explicit Squares(lint arg):
        arg(arg){
    }
    lint operator*() const {
        // A function can be factored out, but is hardcoded
        return arg * arg;
    }
    Squares& operator++() {
        arg += 1;
        return *this;
    }
    Squares operator++(int) {
        Squares retval = *this;
        ++(*this);
        return retval;
    }
    Squares& operator+=(int n){
        arg += n;
        return *this;
    }
    long long int operator-(const Squares& other){
        return this->arg - other.arg;
    }
    bool operator<(const Squares& other){
        return this->arg < other.arg;
    }
};

class Solution {
public:
    int mySqrt(int x) {
        assert(sizeof(lint) >= 2 * sizeof(int));
        assert(x >= 0);
        // Can't have a global infinity sentinel in random iterator type
        // You'd want (a - b) + b == a for most cases
        Squares zero(0), infty(lint(x) + 1); // <- Here we use an additional bit
        auto lower = std::upper_bound(zero, infty, x);
        return int(lower - zero) - 1;
    }
};
