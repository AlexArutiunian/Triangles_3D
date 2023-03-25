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
    
    vector<T>& operator-=(const vector<T>& rhs){
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

template <typename T>
vector<T> operator-(const vector<T>& vect1, const vector<T>& vect2){
    vector<T> temp = vect1;
    temp -= vect1;
    return temp;
}


template <typename T> class line_segment{
private:
    vector<T> point1;
    vector<T> point2;
public:
    line_segment(const vector<T>& p1, const vector<T>& p2):
    point1(p1), point2(p2){
        
    }

    const vector<T> get_point1(){
        return point1;
    }

    const vector<T> get_point2(){
        return point2;
    }

    line_segment(const T* p1, const T* p2){
       
        point1.x = p1[0];
        point1.y = p1[1];
        point1.z = p1[2];

        point2.x = p2[0];
        point2.y = p2[1];
        point2.z = p2[2];

    }

    line_segment<T>& operator=(const line_segment<T>& rhs){
        point1 = rhs.point1;
        point2 = rhs.point2;
        return *this;
    }

    // it is for plane 2D



    bool is_intersect_segment(const line_segment<T>& rhs_segment){
        vector<T> point__1 = rhs_segment.point1;
        vector<T> point__2 = rhs_segment.point2;
      
        vector<T> v1_1 = point__1 - point1;
        vector<T> v2_1 = point__1 - point2;

        vector<T> v1_2 = point__2 - this->point1;
        
        vector<T> v2_2 = point__2 - this->point2;

        vector<T> check1 = v1_1;
        check1.vect_mult(v2_1);
        vector<T> check2 = v1_2;
        check2.vect_mult(v2_2);

        if((check1 * check2) == 0){
           
            if(is_in_interval(point__1, point1, point2) || is_in_interval(point__2, point1, point2)) return true;
            else return false;
        }
        
        if(check1 * check2 < 0){
            // in this case
            // we need to check 
            // projection on one of a segment
            vector<T> direct_v = point1 - point2;
            T free_part1 = direct_v.get_x() * point1.get_y() - direct_v.get_y() * point1.get_x();
            T free_part2 = direct_v.get_y() * point2.get_y() - direct_v.get_x() * point2.get_x();
            
            T summ_quad = direct_v.get_x() * direct_v.get_x() + direct_v.get_y() * direct_v.get_y();

            vector<T> is_in_segment1((free_part2 * direct_v.get_x() - free_part1 * direct_v.get_y()) / summ_quad,
            (free_part1 * direct_v.get_x() + free_part2 * direct_v.get_y()) / summ_quad, 0);

            vector<T> point__1 = rhs_segment.point1;
            vector<T> point__2 = rhs_segment.point2;

            direct_v = point__1 - point__2;

            free_part1 = direct_v.get_x() * point__1.get_y() - direct_v.get_y() * point__1.get_x();
            free_part2 = direct_v.get_y() * point__2.get_y() - direct_v.get_x() * point__2.get_x();
            
            summ_quad = direct_v.get_x() * direct_v.get_x() + direct_v.get_y() * direct_v.get_y();

            vector<T> is_in_segment2((free_part2 * direct_v.get_x() - free_part1 * direct_v.get_y()) / summ_quad,
            (free_part1 * direct_v.get_x() + free_part2 * direct_v.get_y()) / summ_quad, 0);
          
            if(is_in_interval(is_in_segment1, point1, point2) || 
            is_in_interval(is_in_segment2, point__1, point__2)){
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


template <typename T>
bool is_in_interval(vector<T>& is_in_segment1, vector<T>& point1, vector<T>& point2){
    if(((is_in_segment1.get_x() >= point1.get_x() && is_in_segment1.get_x() <= point2.get_x()
        && is_in_segment1.get_y() >= point1.get_y() && is_in_segment1.get_y() <= point2.get_y()) ||
        (is_in_segment1.get_x() <= point1.get_x() && is_in_segment1.get_x() >= point2.get_x()
        && is_in_segment1.get_y() <= point1.get_y() && is_in_segment1.get_y() >= point2.get_y())))
        return true;
    return false;    
}

template <typename T> class triangle{
private:
    vector<T> vert1;
    vector<T> vert2;
    vector<T> vert3;

public:    
    triangle(const vector<T> vert1, const vector<T> vert2, const vector<T> vert3):
    vert1(vert1), vert2(vert2), vert3(vert3){}

    triangle<T>& operator=(const triangle<T>& rhs){
        this->vert1 = rhs.vert1;
        this->vert2 = rhs.vert2;
        this->vert3 = rhs.vert3;

        return *this;
    }

    triangle<T>& operator=(const vector<T>* rhs){
        this->vert1 = rhs[0];
        this->vert2 = rhs[1];
        this->vert3 = rhs[2];

        return *this;
    }
    
    bool is_intersect_triangles(const triangle<T>& tr_rhs){
        line_segment<T> side_11(vert1, vert2);
        line_segment<T> side_12(vert2, vert3);
        line_segment<T> side_13(vert1, vert3);
        
        line_segment<T> side_21(tr_rhs.vert1, tr_rhs.vert2);
        line_segment<T> side_22(tr_rhs.vert2, tr_rhs.vert3);
        line_segment<T> side_23(tr_rhs.vert1, tr_rhs.vert3);

        std::vector<line_segment<T>> sides_tr1({side_11, side_12, side_13});
        std::vector<line_segment<T>> sides_tr2({side_21, side_22, side_23});

        for(int i = 0; i != 3; ++i){
            for(int j = 0; j != 3; ++j){
                if(sides_tr1[i].is_intersect_segment(sides_tr2[j])){ 
                    
                    return true;
                }    
                  
            }

        }
        return false;
        
        
    }
    
    ~triangle(){}
};

     
} // namespace end
