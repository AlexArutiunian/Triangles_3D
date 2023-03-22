#include <vector>
#include "matrix.hpp"

namespace geom{

template <typename T> class point{
private:
// (or protected - for access in derived??)
    T x;
    T y;
    T z;

public:
    point(const T& x; const T& y; const T&z): x(x), y(y), z(z) {};
    ~point(){};
};

template <typename T> class triangle{
protected:
    point<T> A;
    point<T> B;
    point<T> C;

public:
    triangle(point<T>& A, point<T>& B, point<T>& C){
        this->A = A;
        this->B = B;
        this->C = C;
    }
    ~triangle(){};
};  
     
} // namespace end
