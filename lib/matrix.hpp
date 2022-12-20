#pragma once 

#include <iostream>
#include <algorithm>
#include <math.h>

namespace matrix{
template <typename T> class matrix_{
private:
    size_t rows;     
    size_t colons; 
    T* p_matrix;

protected:
    size_t get_rows() const{
        return this->rows;
    }
    size_t get_colons() const{
        return this->colons;
    }
    T* get_elems() const{
        return this->p_matrix;
    }

public:   
    // two constuctors for matrix size of NxM

    matrix_(size_t rs, size_t cs): rows(rs), colons(cs){
        p_matrix = new T[rs * cs];
        if(rs == cs){
            for(size_t i = 1; i != rs + 1; ++i){
                /*first way*/

                //p_matrix[rs * i + i] = 1;

                /*second way
                in which order of operations is important */

                (*(this))(i, i) = 1;
            }
        }
    }     

    matrix_(size_t rs, size_t cs, std::initializer_list<T> elems_matrix): rows(rs), colons(cs){
        p_matrix = new T[cs * rs];

        /*
        // using more quick function copy (copying of 8 bites for one iteration)
        // than for(...) (copying of 1 bites for one iteration)
        */

        std::copy(elems_matrix.begin(), elems_matrix.end(), p_matrix);
    }

    // two constuctors for matrix size of NxN (square_matrix)
    
    matrix_(size_t size_m): rows(size_m), colons(size_m){
        p_matrix = new T[size_m * size_m]; 
        for(size_t i = 1; i != rows + 1; ++i){
            (*(this))(i, i) = 1;
        }
    }

    matrix_(size_t size_m, std::initializer_list<T> elems_matrix): rows(size_m), colons(size_m){
        p_matrix = new T[size_m * size_m];
        std::copy(elems_matrix.begin(), elems_matrix.end(), p_matrix);
    }

    matrix_(size_t rs, size_t cs, T* elems_matrix): rows(rs), colons(cs){
        p_matrix = new T[cs * rs];
        std::copy(elems_matrix[0], elems_matrix[cs * rs - 1], p_matrix);
    }
    
    
    /*
    // the Rule of five
    */
   
    matrix_(const matrix_& other_matrix): rows(other_matrix.rows), colons(other_matrix.colons){
        p_matrix = new T[other_matrix.colons * other_matrix.rows];
        std::copy_n(other_matrix.p_matrix, colons * rows, p_matrix);
    }
    
    matrix_(matrix_&& other_matrix): p_matrix(nullptr), rows(0), colons(0){ 
        swap(other_matrix);
    }


    matrix_& operator= (matrix_& other_m){
        matrix_ copy_(other_m);
        swap(copy_);
        return *this;
    }

    matrix_& operator= (matrix_&& other_m){
        swap(other_m);
        return *this;
    }
   
    ~matrix_(){
        delete[] p_matrix; 
    }


private:     
     
    void swap(matrix_& m){
        std::swap(p_matrix, m.p_matrix);
        std::swap(colons, m.colons);
        std::swap(rows, m.rows);
    }

public:

    T& operator() (const size_t i, const size_t j){
        return p_matrix[colons * (i - 1)  + (j - 1)];
    }

    matrix_& operator= (std::initializer_list<T> elems_matrix){
        p_matrix = new T[elems_matrix.size()];
        assert(elems_matrix.size() == colons * rows);
        std::copy(elems_matrix.begin(), elems_matrix.end(), p_matrix);
        return *this;
    }

    matrix_& operator+= (const matrix_& other_m){
        for(int i = 0; i != other_m.colons * other_m.rows; ++i){
            this->p_matrix[i] += other_m.p_matrix[i];
        }
        return *this;
    }

    matrix_& operator-= (const matrix_& other_m){
        for(int i = 0; i != other_m.colons * other_m.rows; ++i){
            this->p_matrix[i] -= other_m.p_matrix[i];
        }
        return *this;
    }

    matrix_& read(std::istream& is, matrix_& m){
        for(int i = 0; i < static_cast<int>(m.colons * m.rows); ++i){
            is >> m.p_matrix[i];    
        }
        return m;
    }

    /*
    // method for stream output
    // to overload operator <<
    */

    void print(std::ostream& os){
        for(int i = 1; i <= static_cast<int>(colons * rows); ++i){
            os << p_matrix[i - 1] << " ";  
            if(i % colons == 0) os << '\n';   
        }
    }
};   

/*
// overload operator >>
// with method 'read' in class matrix_
*/

template <typename T>
std::istream& operator>> (std::istream& is, matrix_<T>& m){
    m.read(is, m);
    return is;
} 

/*
// overload operator <<
// with method 'print' in class matrix_
*/

template <typename T>
std::ostream& operator<< (std::ostream& os, matrix_<T>& m){
    m.print(os);
    return os;
}

/*
// derived class for more 
// mathematical operations with matrices 
*/

template <typename T> 
class math_matrix: public matrix_<T> {
private: 
    using base_ = matrix_<T>;
   /* auto& colons_ = base_::colons;
    using rows_ = base_<T>::rows;
    using p_elements = base_<T>::p_matrix;*/
public:
    
    math_matrix(size_t rs, size_t cs): 
    base_::matrix_(rs, cs) {}

    math_matrix(size_t n): 
    base_::matrix_(n) {}

    template <typename other_matrix_type = T>
    math_matrix(const matrix_<other_matrix_type>& other_m): 
    matrix_<other_matrix_type>::matrix_(other_m) {}

    math_matrix(size_t rs, size_t cs, std::initializer_list<T> elems_matrix):
    base_::matrix_(rs, cs, elems_matrix) {}

    math_matrix(size_t n, std::initializer_list<T> elems_matrix):
    base_::matrix_(n, elems_matrix) {}

    virtual ~math_matrix(){}
 
    /*
    // method for elementary transformations 1st type
    // swap rows
    */

    void fst_E(int n1, int n2){
        T temp;
        n1 -= 1;
        n2 -= 1;

        size_t cs = base_::get_colons();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();

        for(int i = 0; i != static_cast<int>(cs); ++i){
            temp = p_m[cs * n1 + i];
            p_m[cs * n1 + i] = p_m[cs * n2 + i];
            p_m[cs * n2 + i] = temp;
        }
    }

    /*
    // method for elementary transformations 2nd type
    // row * a, a != 0
    */

    void snd_E(int n, T a){
        n -= 1;

        size_t cs = base_::get_colons();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();

        for(int i = 0; i != cs; ++i){
            p_m[cs * n + i] *= a;  
        }
    }

    /*
    // method for elementary transformations 3rd type
    // row1 = row1 + row2 * a
    */

    void trd_E(int n1, int n2, T a, T EPS){
        n1 -= 1;
        n2 -= 1;
        
        size_t cs = base_::get_colons();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();

        for(int i = 0; i != static_cast<int>(cs); ++i){
            p_m[cs * n1 + i] += a * p_m[cs * n2 + i];
            if(fabs(p_m[cs * n1 + i]) <= EPS){
                p_m[cs * n1 + i] = 0;   
            }    
        }
    }

    int triang_form(T EPS){

        size_t cs = base_::get_colons();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();

        // variable 'permutation' for 
        // the control of swaping rows

        int permutation = 0;
        
        for(int i = 0; i != rs; ++i){
            for(int j = i + 1; j != cs; ++j){
                if(p_m[(cs + 1) * i] == 0){
                    permutation += 1;
                    this->fst_E(j + 1, i + 1); 
                }    
                else this->trd_E(j + 1, i + 1, -(p_m[cs * j + i] / p_m[(cs + 1) * i]), EPS);  
            }              
        }  
        return permutation;     
    }

    T det(T EPS){

        size_t cs = base_::get_colons();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();

        int per = this->triang_form(EPS);
        T det = 0;
        
        if(cs == rs){
            if(p_m[cs * rs - 1] != 0){
                det = p_m[0];
                for(int i = 1; i != static_cast<int>(cs); ++i)
                    det *= p_m[(cs + 1) * i];
            }  
            else return 0;
        }
        
        if(per != 0){
            for(int i = 0; i != per; ++i){
                det *= (-1);
            }
        }
        if(cs != rs) std::cout << "It is not square matrix. I can not solve determinant" << std::endl;
        return det;
    }  

    T det(){
        T EPS = 0.000001;

        size_t cs = base_::get_colons();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();

        int per = this->triang_form(EPS);
        T det = 0;
        
        if(cs == rs){
            if(p_m[cs * rs - 1] != 0){
                det = p_m[0];
                for(int i = 1; i != static_cast<int>(cs); ++i)
                    det *= p_m[(cs + 1) * i];
            }  
            else return 0;
        }
        
        if(per != 0){
            for(int i = 0; i != per; ++i){
                det *= (-1);
            }
        }
        if(cs != rs) std::cout << "It is not square matrix. I can not solve determinant" << std::endl;
        return det;
    }  
}; 

} // namespace matrix
