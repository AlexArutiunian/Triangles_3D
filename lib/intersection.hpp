#include <vector>
#include <cmath>
#include "geom.hpp"

namespace geom{

template <typename T>
bool is_point_in_segment(vector<T>& is_in_segment1, vector<T>& point1, vector<T>& point2){
    if((is_in_segment1 - point1) * (is_in_segment1 - point2) <= 0)
        return true;
    return false;    
}

template <typename T>
bool is_intersect_segment(const line_segment<T>& segment1, const line_segment<T>& segment2){
    vector<T> point__1 = segment1.get_point1();
    vector<T> point__2 = segment1.get_point2();

    vector<T> point1 = segment2.get_point1();
    vector<T> point2 = segment2.get_point2();
    
    vector<T> v1_1(point__1);
    v1_1 = point__1 - point1;
    vector<T> v2_1 = point__1 - point2;

    vector<T> v1_2 = point__2 - point1;
    
    vector<T> v2_2 = point__2 - point2;

    vector<T> check1 = v1_1;
    check1.vect_mult(v2_1);
    vector<T> check2 = v1_2;
    check2.vect_mult(v2_2);

    if((check1 * check2) == 0){
        
        if(is_point_in_segment(point__1, point1, point2) || 
        is_point_in_segment(point__2, point1, point2) || 
        is_point_in_segment(point1, point__1, point__2) ||
        is_point_in_segment(point2, point__1, point__2)) return true;
        else return false;
    }
    
    if(check1 * check2 < 0){
        // in this case
        // we need to check 
        // is point of intersect
        // lines in interval of 
        // one of the segment
        vector<T> direct1 = point1 - point2;
        vector<T> direct2 = point__1 - point__2;
        
        if(direct1.get_y() * direct2.get_x() - direct2.get_y() * direct1.get_x() == 0){
            // case when lines is ||
            return false;
        }

        T x = (direct2.get_x() * direct1.get_x() * point__2.get_y()
        - direct1.get_x() * direct2.get_x() * point1.get_y() + 
        direct1.get_y() * direct2.get_x() * point1.get_x() -
        direct2.get_y() * direct1.get_x() * point__2.get_x()) / 
        (direct1.get_y() * direct2.get_x() - direct2.get_y() * direct1.get_x());

        T y = (direct2.get_y() * direct1.get_y() * (point__2.get_x() - point1.get_x()) +
        direct2.get_y() * direct1.get_x() * point1.get_y() - direct2.get_x() * direct1.get_y() * point__2.get_y()) /
        (direct2.get_y() * direct1.get_x() - direct2.get_x() * direct1.get_y());

        vector<T> is_in_segment1(x, y, 0);

       

        if(is_point_in_segment(is_in_segment1, point1, point2) 
        && is_point_in_segment(is_in_segment1, point__1, point__2)){
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

template <typename T>
bool is_point_in_triangle_2D(const vector<T>& point_, const triangle<T>& triang){
    vector<T> p1 = triang.get_v1();
    vector<T> p2 = triang.get_v2();
    vector<T> p3 = triang.get_v3();

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


template <typename T>
bool is_intersect_triangles_2D(const triangle<T>& tr_1, const triangle<T>& tr_2){
   
    line_segment<T> side_11(tr_1.get_v1(), tr_1.get_v2());
    line_segment<T> side_12(tr_1.get_v2(), tr_1.get_v3());
    line_segment<T> side_13(tr_1.get_v1(), tr_1.get_v3());
    
    line_segment<T> side_21(tr_2.get_v1(), tr_2.get_v2());
    line_segment<T> side_22(tr_2.get_v2(), tr_2.get_v3());
    line_segment<T> side_23(tr_2.get_v1(), tr_2.get_v3());

    std::vector<line_segment<T>> sides_tr1({side_11, side_12, side_13});
    std::vector<line_segment<T>> sides_tr2({side_21, side_22, side_23});

    for(int i = 0; i != 3; ++i){
        for(int j = 0; j != 3; ++j){
            if(is_intersect_segment(sides_tr1[i], sides_tr2[j])){ 
                
                return true;
            }    
                
        }

    }

    
    if(is_point_in_triangle_2D(tr_2.get_v1(), tr_1) 
    || is_point_in_triangle_2D(tr_2.get_v2(), tr_1) 
    || is_point_in_triangle_2D(tr_2.get_v3(), tr_1)){
        return true;
    }

    

    else if(is_point_in_triangle_2D(tr_1.get_v1(), tr_2) 
    || is_point_in_triangle_2D(tr_1.get_v2(), tr_2) 
    || is_point_in_triangle_2D(tr_1.get_v3(), tr_2)){
        return true;
    }

    return false;
    
    
}

}// namespace end