#include <vector>
#include <cmath>
#include "matrix.hpp"
#include <utility>


namespace geom{

template <class T> class vector{
private:
    T x;
    T y;
    T z;
   
public:
    vector = default;

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

    vector<T>& operator +=(const vector<T>& rhs){
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
    }
     
    vector<T>& operator=(T* array){
        x = array[0];
        y = array[1];
        z = array[2];
        return *this;

    }

    T operator * (const vector<T>& rhs){
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    vector<T> vector_mul(const vector<T>& rhs){//Странное возвращение менять this and return: 
        T temp_x = y * rhs.z - z * rhs.y;      //Решил, что удобнее будет просто возвращать изменненный вектор
        T temp_y = z * rhs.x - x * rhs.z ;
        T temp_z = x * rhs.y - y * rhs.x;

        vector<T> temp(temp_x, temp_y, temp_z);

        return temp;
    }

    ~vector(){}
};

template <class T>
vector<T> operator-(const vector<T>& vect1, const vector<T>& vect2){
    vector<T> temp = vect1;
    temp -= vect2;
    return temp;
}

template <class T>
vector<T> operator+(const vector<T>& vect1, const vector<T>& vect2){
    vector<T> temp = vect1;
    temp += vect2;
    return temp;
}


//Line Segment?
template <class T> class line_segment{
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
      
        vector<T> v1_1(point__1);
        v1_1 = point__1 - point1;
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


template <class T>
bool is_in_interval(vector<T>& is_in_segment1, vector<T>& point1, vector<T>& point2){
    if(((is_in_segment1.get_x() >= point1.get_x() && is_in_segment1.get_x() <= point2.get_x()
        && is_in_segment1.get_y() >= point1.get_y() && is_in_segment1.get_y() <= point2.get_y()) ||
        (is_in_segment1.get_x() <= point1.get_x() && is_in_segment1.get_x() >= point2.get_x()
        && is_in_segment1.get_y() <= point1.get_y() && is_in_segment1.get_y() >= point2.get_y())))
        return true;
    return false;    
}

//TRIANGLE
template <class T> class triangle{
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

    vector<T>& get_v1(){
        return vert1;
    }

    vector<T>& get_v2(){
        return vert2;
    }

    vector<T>& get_v3(){
        return vert3;
    }

    bool is_point_in_triangle(const vector<T>& point_){
        vector<T> p1 = vert1;
        vector<T> p2 = vert2;
        vector<T> p3 = vert3;

        vector<T> point = point_;

        p2 -= p1;
        p3 -= p1;
        point -= p1;
       

        T m = (point.get_x() * p2.get_y() - point.get_y() * p2.get_x()) / (p3.get_x() * p2.get_y() - p3.get_y() * p2.get_x());

        if(m >= 0 && m <= 1){
            T l = (point.get_x() - m * p3.get_x()) / p2.get_x();
            if(l >= 0 && ((m + l) <= 1)) return true;
        }

        return false;
    }
    
    bool is_intersect_triangles(const triangle<T>& tr_2){
        triangle<T> tr_rhs = tr_2;
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

       
        if(is_point_in_triangle(tr_rhs.vert1) || is_point_in_triangle(tr_rhs.vert2) || is_point_in_triangle(tr_rhs.vert3)){
            return true;
        }

        else if(tr_rhs.is_point_in_triangle(vert1) || tr_rhs.is_point_in_triangle(vert2) || tr_rhs.is_point_in_triangle(vert3)){
            return true;
        }
    
        return false;
    }
    
    bool tree_perpendiculars(triangle &A);
    vector<T> triangle<T>::value_for_equa(vector<T>& guid_vec, vector<T>& dis);
    vector<T> triangle<T>::search_distance(vector<T>& normal, const T d);
    vector<T> normal();
    ~triangle(){}
};
} // namespace end

// This is part for Triangle3D

template <class T>
geom::vector<T> geom::triangle<T>::normal(){
    vector<T> normal = (vert2-vert1).vector_mul(vert3 - vert1);//N = (V2-V1) x (V3-V1)
    return normal;
}

template <class T>
bool geom::triangle<T>::tree_perpendiculars(triangle<T> &A){

    vector<T> normal_2 = A.normal();                     //Vector N2
    T d_2 = -1 * (normal_2 * A.vert1);                   //d_V2 = -1 * (N2 * V2_1)    
    vector<T> d_1 = this->search_distance(normal_2, d_2);// Далее создается полная абстракция для упрощения работы используется класс вектор 

    if((d_1.x * d_1.y > 0) && (d_1.y * d_1.z > 0)){
        return false;
    }

    vector<T> normal_1 = this->normal();
    T d_1 = -1 * (normal_1 * this->vert1);
    vector<T> d_2 = A.search_distance(normal_1, d_1);

    vector<T> guid_vec = normal_1.vector_mul(normal_2);  //D = N1 x N2

    vector<T> t_1 = this->value_for_equa(guid_vec, d_1);
    vector<T> t_2 = A.value_for_equa(guid_vec, d_2);

    if((t_1.x < t_2.x && t_2.x < t_1.y) || (t_1.x < t_2.y && t_2.y < t_1.y)){
        return true;
    }
    
    return false;
}

template <class T>
geom::vector<T> geom::triangle<T>::search_distance(vector<T>& normal, const T dis){
    vector<T> d;
    d.x = normal_2 * this->vert1 + dis;             //d_V1_i = N2*V1_i + d_V2
    d.y = normal_2 * this->vert2 + dis; 
    d.z = normal_2 * this->vert3 + dis;

    return d; 
}

template <class T>
geom::vector<T> geom::triangle<T>::value_for_equa(vector<T>& guid_vec, vector<T>& dis){
    p_1 = guid_vec * this->vert1;
    p_2 = guid_vec * this->vert2;
    p_3 = guid_vec * this->vert3;

    if(dis.x * dis.z > 0){
        t1 = p_1 + (p_2 - p_1)*(dis.x)/(dis.x - dis.y);
        t2 = p_3 + (p_2 - p_3)*(dis.z)/(dis.z - dis.y);
    }
    if(dis.y * dis.z > 0){
        t1 = p_2 + (p_1 - p_2)*(dis.y)/(dis.y - dis.x);
        t2 = p_3 + (p_1 - p_3)*(dis.z)/(dis.z - dis.x);
    }
    if(dis.x * dis.y > 0){
        t1 = p_1 + (p_3 - p_1)*(dis.x)/(dis.x - dis.z);
        t2 = p_2 + (p_3 - p_2)*(dis.y)/(dis.z - dis.z);
    }

    vector<t> t(t1, t2, NAN);
    return t;
}

