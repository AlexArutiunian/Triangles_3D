#pragma once 

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cassert>


namespace matrix{

template <typename T> void construct(T *p, T &rhs){
    new (p) T(rhs);
}

template <typename T> void destroy(T *p) noexcept{
    p->~T();
}

template <typename F> void destroy(F first, F last) noexcept {
    // dctor impossible to make 
    // non-dangerous for exception 
    // and we do it noexcept 
    while(first++ != last)
        destroy(&*first);
}

// class for control
// of raw memory

template <typename T> struct matrix_buf{
protected:
    T *arr_;
    size_t size_;
    size_t used_ = 0;
    // ban for copying 
    matrix_buf(const matrix_buf &) = delete;  
    // ban for copying assignment
    matrix_buf &operator=(const matrix_buf &) = delete;

    
    matrix_buf (matrix_buf &&rhs) noexcept:
    arr_(rhs.arr_), size_(rhs.size_), used_(rhs.used_){
        rhs.arr = nullptr;
        rhs.size_ = 0;
        rhs.used_ = 0;
    }  

    // moving by just swap pointers
    matrix_buf &operator=(matrix_buf &&rhs) noexcept{
        std::swap(arr_, rhs.arr_);
        std::swap(size_, rhs.size_);
        std::swap(used_, rhs.used_);
        return *this;
    }

  
    // most interesting is constructor

    matrix_buf(size_t sz = 0){
        if(sz == 0){
            arr_ = nullptr;
        }
        else{
            try{
                arr_ = static_cast<T*>(::operator new(sizeof(T) * sz));
            }catch(std::bad_alloc){
                std::cout << "Error with mem alloc\n";
                throw;
            }
            
        }
        size_ = sz;
       

            // mem alloc 
            // safety for exceptions
            // if exceptions is
            // object does not start existing
      
    }

    ~matrix_buf(){
        destroy(arr_, arr_ + used_);
        ::operator delete(arr_);
    }

};

// safety mem alloc
// with class matrix_buf
// if mem alloc - OK
// is not exceptions

template <typename T> class matrix_ : private matrix_buf<T>{
private:
    size_t rows;     
    size_t columns; 
    T* p_matrix;

protected:
    size_t get_rows() const{
        return this->rows;
    }
    size_t get_columns() const{
        return this->columns;
    }
    T* get_elems() const{
        return this->p_matrix;
    }

public:   

    using matrix_buf<T>::used_;
    using matrix_buf<T>::size_;
    using matrix_buf<T>::arr_;

    // two constuctors for matrix size of NxM
    
    // safety ctor with using
    // class matrix_buf
    matrix_(size_t rs, size_t cs): matrix_buf<T>(rs * cs) {
        p_matrix = arr_;
        rows = rs;
        columns = cs;
        for(size_t i = 1; i != rows + 1; ++i){
            for(size_t j = 1; j != columns + 1; ++j){
                T temp = 0;
                T &ref_t = temp;
                construct(arr_ + used_, ref_t);
                used_ += 1;   
            }         
        } 
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

    matrix_(size_t rs, size_t cs, std::initializer_list<T> elems_matrix):
    matrix_buf<T>(rs * cs) {
        rows = rs;
        columns = cs;
        p_matrix = arr_;

        for(auto elem : elems_matrix){
            construct(arr_ + used_, elem);
            used_ += 1;
        }
    }

    // two constuctors for matrix size of NxN (square_matrix)
    
    matrix_(size_t size_m): matrix_buf<T>(size_m * size_m){

        rows = size_m;
        columns = size_m;
        p_matrix = arr_;
      
        for(size_t i = 1; i != rows + 1; ++i){
            for(size_t j = 1; j != columns + 1; ++j){
                T temp = 0;
                T &ref_t = temp;
                construct(arr_ + used_, ref_t);
                used_ += 1;
            }
               
        
        } 
        for(size_t i = 1; i != rows + 1; ++i){
            (*(this))(i, i) = 1;
        }
        
        
    }

    matrix_(size_t size_m, std::initializer_list<T> elems_matrix):
    matrix_buf<T>(size_m * size_m),
    rows(size_m), columns(size_m){
        p_matrix = arr_;
        for(auto elem : elems_matrix){
            construct(arr_ + used_, elem);
            used_ += 1;
        }   
    }

    matrix_(size_t rs, size_t cs, T* elems_matrix): matrix_buf<T>(rs * cs),
    rows(rs), columns(cs){
        p_matrix = arr_;
        for(size_t i = 0; i != rs * cs; ++i){
            construct(arr_ + used_, elems_matrix[i]);
            used_ += 1;
        }  
    }
    
    
    /*
    // the Rule of five
    */
   
    matrix_(const matrix_& other_matrix): matrix_buf<T>(other_matrix.used_){
        rows = other_matrix.rows;
        columns = other_matrix.columns;
        p_matrix = other_matrix.arr_;
        while (used_ < other_matrix.used_) {
            construct(arr_ + used_, other_matrix.arr_[used_]);
            used_ += 1;
        }
    }
    
    matrix_(matrix_&& other_matrix) noexcept: p_matrix(nullptr), rows(0), columns(0) { 
        swap(other_matrix);
    }


    matrix_& operator= (matrix_& other_m) noexcept{
        matrix_ copy_(other_m);
        swap(copy_);
        return *this;
    }

    matrix_& operator= (matrix_&& other_m) noexcept{
        swap(other_m);
        return *this;
    }
   
   


protected:     
     
    void swap(matrix_& m) noexcept{
        std::swap(p_matrix, m.p_matrix);
        std::swap(columns, m.columns);
        std::swap(rows, m.rows);
    }

public:

    T& operator() (const size_t i, const size_t j){
        return p_matrix[columns * (i - 1)  + (j - 1)];
    }

    matrix_& operator= (std::initializer_list<T> elems_matrix){
        if(rows * columns != elems_matrix.size()){
            throw std::runtime_error("Bad initializing");
        } 
        std::copy(elems_matrix.begin(), elems_matrix.end(), p_matrix);

        return *this;
    }

    matrix_& operator+= (const matrix_& other_m){
        for(int i = 0; i != other_m.columns * other_m.rows; ++i){
            this->p_matrix[i] += other_m.p_matrix[i];
        }
        return *this;
    }

    matrix_& operator-= (const matrix_& other_m){
        for(int i = 0; i != other_m.columns * other_m.rows; ++i){
            this->p_matrix[i] -= other_m.p_matrix[i];
        }
        return *this;
    }

    matrix_& read(std::istream& is, matrix_& m){
        for(int i = 0; i < static_cast<int>(m.columns * m.rows); ++i){
            is >> m.p_matrix[i];    
        }
        return m;
    }

    /*
    // method for stream output
    // to overload operator <<
    */

    void print(std::ostream& os) noexcept{
        for(int i = 1; i <= static_cast<int>(columns * rows); ++i){
            os << p_matrix[i - 1] << " ";  
            if(i % columns == 0) os << '\n';   
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
   /* auto& columns_ = base_::columns;
    using rows_ = base_<T>::rows;
    using p_elements = base_<T>::p_matrix;*/

    void check_col(int n1, int n2) const{
        size_t cs = base_::get_columns();
       
        if((n1 >= cs) || (n2 >= cs))
            throw std::invalid_argument("Don't touch alien memory!");
    }

    void check_row(int n1, int n2) const{
       
        size_t rs = base_::get_rows();
        if((n1 >= rs) || (n2 >= rs))
            throw std::invalid_argument("Don't touch alien memory!");
    }

    void message_row_none(int n1, int n2) noexcept{
        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        std::cout << "row " << n1 + 1 << " or row "
        << n2 + 1 << " does not exist" 
        << " in matrix " << rs << "x" << cs << std::endl;
    }

    void message_col_none(int n1, int n2) noexcept{
        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        std::cout << "column " << n1 + 1 << " or column "
        << n2 + 1 << " does not exist" 
        << " in matrix " << rs << "x" << cs << std::endl;
    }

    void message_one_row(int n) noexcept{
        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        std::cout << "row " << n + 1
        << " does not exist" 
        << " in matrix " << rs << "x" << cs << std::endl;
}

    
    
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

    math_matrix(size_t rs, std::initializer_list<T> elems_matrix):
    base_::matrix_(rs, elems_matrix) {}

    math_matrix(size_t rs, size_t cs, T* elems_matrix):
    base_::matrix_(rs, cs, elems_matrix) {}

    math_matrix& operator=(std::initializer_list<T> elems_matrix){
        base_::operator=(elems_matrix);
        return *this;
    }   

    math_matrix& operator=(base_& other_m){
        base_::operator=(other_m);
        return *this;
    }

    math_matrix& operator=(math_matrix& other_m){
        matrix_ copy_(other_m);
        base_::swap(copy_);
        return *this;
    }
    math_matrix& operator=(math_matrix&& other_m){
        base_::swap(other_m);
        return *this;
    }

    
 
    /*
    // method for elementary transformations 1st type
    // swap rows
    */

    void fst_E(int n1, int n2){
        row_swap(n1, n2);
    }

    /*
    // method for elementary transformations 2nd type
    // row * a, a != 0
    */

    void snd_E(int n, T a){
        n -= 1;
        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();
        check_row(n, n);
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
        
        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();
        
        check_row(n1, n2); 

        for(int i = 0; i != static_cast<int>(cs); ++i){
            p_m[cs * n1 + i] += a * p_m[cs * n2 + i];
            if(fabs(p_m[cs * n1 + i]) <= EPS){
                p_m[cs * n1 + i] = 0;   
            }    
        }
        
    }
    

    void row_swap(int n1, int n2){

        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();
    
        T temp;
        n1 -= 1;
        n2 -= 1;

        
        check_row(n1, n2);     
        
        for(int i = 0; i != static_cast<int>(cs); ++i){
            temp = p_m[cs * n1 + i];
            p_m[cs * n1 + i] = p_m[cs * n2 + i];
            p_m[cs * n2 + i] = temp;
        }
        
      
        
    }

    void col_swap(int n1, int n2){
        
        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();
        T temp;
        n1 -= 1;
        n2 -= 1;
        
        
        check_col(n1, n2);  
        
     
        for(int i = 0; i != static_cast<int>(rs); ++i){
            temp = p_m[cs * i + n1];
            p_m[cs * i + n1] = p_m[cs * i + n2];
            p_m[cs * i + n2] = temp;
        }
      
    }

    int triang_form_Gauss_max(T EPS){

        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();

        // variable 'permutation' for 
        // the control of swaping rows

        int permutation = 0;
        

        for(int i = 0; i != rs; ++i){
        
            for(int j = i + 1; j != cs; ++j){
                               
                int j_max = find_max_in_row(i);
                col_swap(j_max, j);
                if(j_max != j)
                    permutation += 1;
                              
                if(p_m[(cs + 1) * i] == 0){
                    
                    permutation += 1;
                    
                    this->fst_E(j + 1, i + 1); 
                }    
                else this->trd_E(j + 1, i + 1, -(p_m[cs * j + i] / p_m[(cs + 1) * i]), EPS);  
            }
                                        
        }        
        return permutation;     
    }

    int find_max_in_row(int i){

       
        check_row(i, i);       
        

        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();
        i += 1;
        T max = p_m[i * cs];
        int i_max = 0;
        for (int j = 1; j != cs; j++) {
            if (abs(p_m[i * cs + j]) > abs(max)) {
                max = p_m[i * cs + j];
                i_max = j;
            }
        }
        return i_max + 1;
    }

    // now only for square matrix

    std::pair<int, int> find_max_(){
        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();
        T max = p_m[0];
        int i_max = 0;
        for (int i = 1; i < cs * rs; ++i) {
            if (abs(p_m[i]) > abs(max)) {
                max = p_m[i];
                i_max = i;
            }
        }
        return std::pair<int, int>(i_max / cs + 1, i_max % cs + 1);
    }  

    int triang_form_Gauss(T EPS){

        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();
        T* p_m = base_::get_elems();

        // variable 'permutation' for 
        // the control of swaping rows

        int permutation = 1;
        

        for(int i = 0; i != rs; ++i){
            for(int j = i + 1; j != cs; ++j){
                if(p_m[(cs + 1) * i] == 0){
                    permutation *= (-1);
                    this->fst_E(j + 1, i + 1); 
                }    
                else this->trd_E(j + 1, i + 1, -(p_m[cs * j + i] / p_m[(cs + 1) * i]), EPS);  
            }              
        }  
        return permutation;     
    }

    T det_Gauss(T EPS){
        size_t cs = base_::get_columns();
        size_t rs = base_::get_rows();

        if (rs != cs) {
            throw std::invalid_argument("Matrix must be square");
        }

        T* p_m = base_::get_elems();
        math_matrix<T> m_copy(cs, rs);


        m_copy = *this;

        int per = m_copy.triang_form_Gauss_max(EPS);
        T det = 0;
        if(cs != rs){
            std::cout << "It is not square matrix. I can not solve determinant" << std::endl;
            return 0;
        }    
        if(cs == rs){
            if(m_copy(cs, cs) != 0){
                det = m_copy(1, 1);
                for(int i = 1; i != static_cast<int>(cs); ++i)
                    det *= m_copy(i + 1, i + 1);
            }  
            else return 0;
        }
        
        
        if(abs(det) == 0) return 0;

        if(per != 0){
            for(int i = 0; i != per; ++i){
                det *= (-1);
            }
        }
       
        return det;
    }    
    T det_Gauss(){

        T EPS = 0.000000000001;
        return det_Gauss(EPS);
    } 

    
}; 

} // namespace matrix
