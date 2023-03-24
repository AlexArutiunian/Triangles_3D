#include <vector>
#include <cmath>
#include "matrix.hpp"
#include <utility>


namespace geom{

template <typename T> class vector{
private:
    T x;
    T y;
    T z;
   
public:
    

    vector(const T& x, const T& y, const T& z): x(x), y(y), z(z){}
    
    vector<T>& operator=(const vector<T>& rhs){
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    } 

    T get_x(){
        return x;
    }
    T get_y(){
        return y;
    }
    T get_z(){
        return z;
    }
    
    vector<T>& operator-(const vector<T>& rhs){
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }
     
    vector<T>& operator=(T* array){
        x = array[0];
        y = array[1];
        z = array[2];
        return *this;

    }

    T operator*(const vector<T>& rhs){
        
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    

    vector<T>& vect_mult(const vector<T>& rhs){
        
        T temp_x = y * rhs.z - z * rhs.y;
        T temp_y = -x * rhs.z + z * rhs.x;
        T temp_z = x * rhs.y - y * rhs.x;

        x = temp_x;
        y = temp_y;
        z = temp_z;

        return *this;
   
    }
    
    ~vector(){}
};

template <typename T> class line_segment{
private:
    vector<T> point1;
    vector<T> point2;
public:
    line_segment(const vector<T>& p1, const vector<T>& p2):
    point1(p1), point2(p2){}

    line_segment(const T* p1, const T* p2){
        point1.x = p1[0];
        point1.y = p1[1];
        point1.z = p1[2];

        point2.x = p2[0];
        point2.y = p2[1];
        point2.z = p2[2];

    }

    // it is for plane 2D

    bool is_intersect_segment(const line_segment<T>& rhs_segment){
        vector<T> v1_1 = this->point1 - rhs_segment.point1;
        vector<T> v2_1 = this->point2 - rhs_segment.point1;

        vector<T> v1_2 = this->point1 - rhs_segment.point2;
        vector<T> v2_2 = this->point2 - rhs_segment.point2;

        vector<T> check1 = v1_1;
        check1.vect_mult(v2_1);
        vector<T> check2 = v1_2;
        check2.vect_mult(v2_2);
        
        if(check1 * check2 <= 0){
            // in this case
            // we need to check 
            // projection on one of a segment
            vector<T> direct_v = point1 - point2;
            T free_part1 = -direct_v.get_x() * point1.get_x() - direct_v.get_y() * point1.get_y();
            T free_part2 = direct_v.get_x() * point2.get_x() - direct_v.get_y() * point2.get_y();
            vector<T> is_in_segment((-free_part1 + free_part2) / (2 * direct_v.get_x()), 
            (-free_part1 - free_part2) / (2 * direct_v.get_y()), 0);
          
            if((is_in_segment.get_x() >= point1.get_x() && is_in_segment.get_x() <= point2.get_x()
            && is_in_segment.get_y() >= point1.get_y() && is_in_segment.get_y() <= point2.get_y()) ||
            (is_in_segment.get_x() <= point1.get_x() && is_in_segment.get_x() >= point2.get_x()
            && is_in_segment.get_y() <= point1.get_y() && is_in_segment.get_y() >= point2.get_y())){
                return true;
            }
            else return false;
        }else{
            // in this case
            // 100% segments dont intersect
            // because all points one segment lie
            // in one side of another segment
            
            return false;
        }

    }

    ~line_segment(){}
};

     
} // namespace end
