#pragma once

#include <vector>
#include <cmath>
#include "geom.hpp"
#include "vector_3D.hpp"
#include "triangle.hpp"
#include "segment.hpp"

namespace geom{
    
template <typename T>
bool is_point_in_segment(vector<T>& is_in_segment1, vector<T>& point1, vector<T>& point2){
    if((is_in_segment1 - point1) * (is_in_segment1 - point2) <= 0)
        return true;
    return false;    
}

template <typename T>
bool is_intersect_segment(const segment<T>& segment1, const segment<T>& segment2){
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
   
    segment<T> side_11(tr_1.get_v1(), tr_1.get_v2());
    segment<T> side_12(tr_1.get_v2(), tr_1.get_v3());
    segment<T> side_13(tr_1.get_v1(), tr_1.get_v3());
    
    segment<T> side_21(tr_2.get_v1(), tr_2.get_v2());
    segment<T> side_22(tr_2.get_v2(), tr_2.get_v3());
    segment<T> side_23(tr_2.get_v1(), tr_2.get_v3());

    std::vector<segment<T>> sides_tr1({side_11, side_12, side_13});
    std::vector<segment<T>> sides_tr2({side_21, side_22, side_23});

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

template <typename T>
T dist_between_point_and_triangle(const triangle<T>& A, const vector<T>& point){
    vector<T> normal_ = A.normal();
    T dis_ = -1 * (normal_ * A.get_v1());                      
    T d = normal_ * point + dis_;
    return d; 
}

template <typename T>
std::vector<T> distance(const triangle<T>& A, const triangle<T>& B){
    std::vector<T> d(3);
    d[0] = dist_between_point_and_triangle(B, A.get_v1());
    d[1] = dist_between_point_and_triangle(B, A.get_v2());
    d[2] = dist_between_point_and_triangle(B, A.get_v3());
    return d;
}

template <typename T>
bool is_intersect_triangles_3D(const triangle<T>& A, const triangle<T>& B){
    
    vector<T> normal_2 = B.normal();

    std::vector<T> d_1 = distance(A, B);

    std::vector<T> d_2 = distance(B, A);
    vector<T> normal_1 = A.normal();

    if(d_1[0] == 0 && d_1[1] == 0 && d_1[2] == 0){
        return is_intersect_triangles_2D(A, B);
    }

    if(((d_1[0] * d_1[1] > 0) && (d_1[1] * d_1[2] > 0)) || ((d_2[0] * d_2[1] > 0) && (d_2[1] * d_2[2] > 0))){
        return false;
    }

    vector<T> guid_vector = normal_1.vect_mult(normal_2);  //D = N1 x N2

    std::vector<T> t_1 = value_for_equal(A, guid_vector, d_1);
    std::vector<T> t_2 = value_for_equal(B, guid_vector, d_2);

    if((t_1[0] <= t_2[0] && t_2[0] <= t_1[1]) || (t_1[0] <= t_2[1] && t_2[1] <= t_1[1])){
        return true;
    }
    
    return false;  
}



template <typename T>
std::vector<T> search_distance(const triangle<T>& A,  const std::vector<T>& normal, const T& dis){
    std::vector<T> d(3);

    d[0] = normal * A.get_v1() + dis;             //d_V1_i = N2*V1_i + d_V2
    d[1] = normal * A.get_v2() + dis; 
    d[2] = normal * A.get_v3() + dis;

    return d; 
}

template <typename T>
std::vector<T> value_for_equal(const triangle<T>& A, const vector<T>& guid_vector, const std::vector<T>& dis){
    T p_1 = guid_vector * A.get_v1();
    T p_2 = guid_vector * A.get_v2();
    T p_3 = guid_vector * A.get_v3();

    std::vector<T> t(2);

    if(dis[0] * dis[2] > 0){
        T temp1 = p_1 + (p_2 - p_1)*(dis[0])/(dis[0] - dis[1]);
        
        T temp2 = p_3 + (p_2 - p_3)*(dis[2])/(dis[2] - dis[1]);
        if(temp1 < temp2){
            t[0] = temp1;
            t[1] = temp2;
        } 
        else{
            t[0] = temp2;
            t[1] = temp1;
        }
    }
    if(dis[1] * dis[2] > 0){
        T temp1 = p_2 + (p_1 - p_2)*(dis[1])/(dis[1] - dis[0]);
        T temp2 = p_3 + (p_1 - p_3)*(dis[2])/(dis[2] - dis[0]);
        if(temp1 < temp2){
            t[0] = temp1;
            t[1] = temp2;
        } 
        else{
            t[0] = temp2;
            t[1] = temp1;
        }
    }
    if(dis[0] * dis[1] > 0){
        T temp1 = p_1 + (p_3 - p_1)*(dis[0])/(dis[0] - dis[2]);
        T temp2 = p_2 + (p_3 - p_2)*(dis[1])/(dis[1] - dis[2]);
        if(temp1 < temp2){
            t[0] = temp1;
            t[1] = temp2;
        } 
        else{
            t[0] = temp2;
            t[1] = temp1;
        }
    }
    return t;
}

template <typename T>
bool tree_perpendiculars(triangle<T> &A, triangle<T> &B){

    vector<T> normal_2 = B.normal();

    T dis_1 = -1 * (normal_2 * B.get_v1());                   //d_V2 = -1 * (N2 * V2_1)    
    std::vector<T> d_1 = search_distance(A, normal_2, dis_1);// Далее создается полная абстракция для упрощения работы используется класс вектор 

    if((d_1[0] * d_1[1] > 0) && (d_1[1] * d_1[2] > 0)){
        return false;
    }

    vector<T> normal_1 = A.normal();

    T dis_2 = -1 * (normal_1 * A.get_v1());
    std::vector<T> d_2 = search_distance(B, normal_1, dis_2);

    vector<T> guid_vector = normal_1.vect_mult(normal_2);  //D = N1 x N2

    std::vector<T> t_1 = value_for_equa(A, guid_vector, d_1);
    std::vector<T> t_2 = value_for_equa(B, guid_vector, d_2);

    if((t_1[0] <= t_2[0] && t_2[0] <= t_1[1]) || (t_1[0] <= t_2[1] && t_2[1] <= t_1[1])){
        return true;
    }
    
    return false;
}
}// namespace end
