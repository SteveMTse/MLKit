#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Math.hpp"
#include "Tools.hpp"

template <typename T, int r = 0, int c = 0>
class Matrix {

    private:
         T** matrix = NULL;
         T** matrix_inv = NULL;
         T zero = 0;
         T one = 1;

         int size = 0;
         int row = 0;
         int col = 0;

         static void computer(Matrix<T>* A, Matrix<T>* B, Matrix<T>* C, int start_row, int end_row, int start_col, int end_col, int* common_dim) {
                if(start_row >= 0 && end_row >= start_row && start_col >= 0 && end_col >= end_col) {
                    for(int i = start_row ; i <= end_row ; i++) {
                        for(int j = start_col ; j <= end_col ; j++) {
                            for(int k = 0 ; k < (*common_dim) ; k++) {
                                (*C)[i][j] += ((*A)[i][k] * (*B)[k][j]);
                            }
                        }
                    }
                }
            }

        void splitor(int** &arg, int r_C, int cm, int c_C) {
                int tau = -1;
                if(r_C >= c_C) {
                    tau = int(r_C/N_Thread);
                    arg[0][0] = 0; arg[0][1] = tau; arg[0][2] = 0; arg[0][3] = c_C - 1;
                    for(int i = 1 ; i < int(N_Thread) ; i++) {
                        if(arg[i-1][1] != -1 && arg[i-1][1] + 1 < r_C) {
                            arg[i][0] = arg[i-1][1] + 1;
                        }
                        else {
                            arg[i][0] = -1;
                        }
                        if(arg[i][0] != -1) {
                            if(arg[i][0] + tau < r_C) {
                                arg[i][1] = arg[i][0] + tau;
                            }
                            else {
                                arg[i][1] = r_C - 1;
                            }
                        }
                        else {
                            arg[i][1] = -1;
                        }
                        if(arg[i][1] != -1) {
                            arg[i][2] = 0; arg[i][3] = c_C - 1;
                        }
                    }
                }
                else {
                    tau = int(c_C/N_Thread);
                    arg[0][0] = 0; arg[0][1] = r_C - 1; arg[0][2] = 0; arg[0][3] = tau;
                    for(int i = 1 ; i < int(N_Thread) ; i++) {
                        if(arg[i-1][3] != -1 && arg[i-1][3] + 1 < c_C) {
                            arg[i][2] = arg[i-1][3] + 1;
                        }
                        else {
                            arg[i][2] = -1;
                        }
                        if(arg[i][2] != -1) {
                            if(arg[i][2] + tau < c_C) {
                                arg[i][3] = arg[i][2] + tau;
                            }
                            else {
                                arg[i][3] = c_C - 1;
                            }
                        }
                        else {
                            arg[i][3] = -1;
                        }
                        if(arg[i][3] != -1) {
                            arg[i][0] = 0; arg[i][1] = r_C - 1;
                        }
                    }
                }
            }

         void MatrixMultipication(Matrix<T> &A, Matrix<T> &B, Matrix<T> &C, int row_C, int common, int col_C) {
            int split_row = int(double(row_C) / len);
            int split_col = int(double(col_C) / len);

            int** index_info = NULL;
            array_initializer<int>(index_info, int(N_Thread), 4, -1);

            this -> splitor(index_info, row_C, common, col_C);

            for(int thread_id = 0 ; thread_id < int(N_Thread) ; thread_id++) {
                thread th(computer, &A, &B, &C, index_info[thread_id][0], index_info[thread_id][1], index_info[thread_id][2], index_info[thread_id][3], &common);
                th.join();
            }

            delete[] index_info;
         }

         inline void LinearEquationSolver(T* &b, T* &x, T** &L, T** &U, T* &y, int &n) {
            
            T sum = zero;

            //Foreward substitution
            
            // x = new T[n];
            for(int i = 0 ; i < n ; i++) { 
                y[i] = zero;
                x[i] = zero;
            }

            for(int k = 0 ; k < n ; k++) {
                for(int j = 0 ; j <= k - 1 ; j++) {
                    sum = sum + (L[k][j] * y[j]);
                }
                y[k] = (b[k] - sum) / L[k][k];
                sum = zero;
            }

            //Backward substitution
            sum = zero;
            for(int k = n - 1 ; k >= 0 ; k--) {
                for(int j = k + 1 ; j < n ; j++) {
                    sum = sum + (U[k][j] * x[j]);
                }
                x[k] = (y[k] - sum) / U[k][k];
                sum = zero;
            }

         }

         void MatrixInverse() {
            
            int n = -1;
            if(this -> col != this -> row) {
                return;
            }
            else {
                n = this -> col;
            }

            T* b = new T[n];
            T* x = new T[n];
            T* y = new T[n];

            T** L = new T*[n];
            T** U = new T*[n];

            //LU Decomposition
            //Initialize L and U;
            for(int i = 0 ; i < n ; i++) {
                L[i] = new T[n];
                U[i] = new T[n];
                for(int j = 0 ; j < n ; j++) {
                    L[i][j] = (j == i) ? 1 : 0;
                    U[i][j] = (this -> matrix)[i][j];
                }
            }

            //LU Factorization
            for(int k = 0 ; k < n - 1 ; k++) {
                for(int j = k+1 ; j < n ; j++) {
                    L[j][k] = U[j][k] / U[k][k];
                    for(int i = k ; i < n ; i++) {
                        U[j][i] = U[j][i] - (L[j][k]*U[k][i]);
                    }
                }
            }

            for(int i = 0 ; i < n ; i++) {
                for(int j = 0 ; j < n ; j++) {
                    b[j] = (i != j) ? 0 : 1;
                }
                this -> LinearEquationSolver(b, x, L, U, y, n);
                for(int j = 0 ; j < n ; j++) {
                    (this -> matrix_inv)[j][i] = x[j];
                }
            }

            delete[] L;
            delete[] U;
            delete[] b;
            delete[] x;
            delete[] y;
         }

    public:

          Matrix() {}

          Matrix(initializer_list<initializer_list<T>> arg) {
              this -> row = arg.size();
              this -> col = (arg.size() != 0) ? (*arg.begin()).size() : 0;
              this -> matrix = new T*[this -> row];
              this -> matrix_inv = new T*[this -> row];
              this -> size = (this -> row) * (this -> col);
              int i = 0, j = 0;
              for(auto && ROW : arg) {
                  (this -> matrix)[i] = new T[this -> col];
                  (this -> matrix_inv)[i] = new T[this -> col];
                  for(auto && COL : ROW) {
                      (this -> matrix)[i][j] = COL;
                      (this -> matrix_inv)[i][j] = zero;
                      j++;
                  }
                  j = 0; i++;
              }
              this -> MatrixInverse();
          }

          Matrix(T arg[r][c]) {
            this -> row = r;
            this -> col = c;
            this -> matrix = new T*[this -> row];
            this -> matrix_inv = new T*[this -> row];
            this -> size = (this -> row) * (this -> col);
            for(int i = 0 ; i < row ; i++) {
                matrix[i] = new T[col];
                (this -> matrix_inv)[i] = new T[this -> col];
                for(int j = 0 ; j < col ; j++) {
                    (this -> matrix)[i][j] = arg[i][j];
                    (this -> matrix_inv)[i][j] = zero;
                }
            }
            this -> MatrixInverse();
          }

          Matrix(T** arg) {
            this -> row = r;
            this -> col = c;
            this -> matrix = new T*[this -> row];
            this -> matrix_inv = new T*[this -> row];
            this -> size = (this -> row) * (this -> col);
            for(int i = 0 ; i < row ; i++) {
                matrix[i] = new T[col];
                (this -> matrix_inv)[i] = new T[this -> col];
                for(int j = 0 ; j < col ; j++) {
                    (this -> matrix)[i][j] = arg[i][j];
                    (this -> matrix_inv)[i][j] = zero;
                }
            }
            this -> MatrixInverse();
          }

          Matrix(T** arg, int arg_row, int arg_col) {
            this -> row = arg_row;
            this -> col = arg_col;
            this -> matrix = new T*[this -> row];
            this -> matrix_inv = new T*[this -> row];
            this -> size = (this -> row) * (this -> col);
            for(int i = 0 ; i < row ; i++) {
                matrix[i] = new T[col];
                (this -> matrix_inv)[i] = new T[this -> col];
                for(int j = 0 ; j < col ; j++) {
                    (this -> matrix)[i][j] = arg[i][j];
                    (this -> matrix_inv)[i][j] = zero;
                }
            }
            this -> MatrixInverse();
          }

          Matrix(int arg_row, int arg_col, T init_val) {
            this -> row = arg_row;
            this -> col = arg_col;
            this -> matrix = new T*[this -> row];
            this -> matrix_inv = new T*[this -> row];
            this -> size = (this -> row) * (this -> col);
            for(int i = 0 ; i < row ; i++) {
                matrix[i] = new T[col];
                (this -> matrix_inv)[i] = new T[this -> col];
                for(int j = 0 ; j < col ; j++) {
                    (this -> matrix)[i][j] = init_val;
                    (this -> matrix_inv)[i][j] = zero;
                }
            }
            this -> MatrixInverse();
          }

          ~Matrix() {
              delete[] this -> matrix;
              delete[] this -> matrix_inv;
              // cout<<"Deleted!"<<endl;
          }

          T*& operator[] (const int arg) {
              return (this -> matrix)[arg];
          }

          int get_row() {
              return this -> row;
          }

          int get_col() {
              return this -> col;
          }

          void set_dim(int arg_row, int arg_col) {
              if(this -> matrix != NULL) {
                  delete[] (this -> matrix);
                  delete[] (this -> matrix_inv);
                  this -> matrix = NULL;
              }
              this -> row = arg_row;
              this -> col = arg_col;
              this -> size = arg_row * arg_col;
              this -> matrix = new T*[this -> row];
              this -> matrix = new T*[this -> row];
              for(int i = 0 ; i < this -> row ; i++) {
                  (this -> matrix)[i] = new T[this -> col];
                  (this -> matrix_inv)[i] = new T[this -> col];
              }
          }

          void update() {
              this -> MatrixInverse();
          }

          T** get_matrix() {
              return this -> matrix;
          }

          Matrix<T> operator* (Matrix<T> &&arg) {
             const int x = this -> row;
             const int y = arg.get_col();
             Matrix<T> ret = Matrix<T>({{}});
             if((this -> col) == arg.get_row()) {
                ret.set_dim(x, y);
                MatrixMultipication(*this, arg, ret, x, this -> col, y);
             }
             return ret;
          }

          Matrix<T> operator* (Matrix<T> &arg) {
             const int x = this -> row;
             const int y = arg.get_col();
             Matrix<T> ret = Matrix<T>({{}});
             if((this -> col) == arg.get_row()) {
                ret.set_dim(x, y);
                MatrixMultipication(*this, arg, ret, x, this -> col, y);
             }
             return ret;
          }

          Matrix<T> transpose() {
              T** mat_trans = new T*[this -> col];
              for(int i = 0 ; i < this -> col ; i++) {
                  mat_trans[i] = new T[this -> row];
                  for(int j = 0 ; j < this -> row ; j++) {
                      mat_trans[i][j] = (this -> matrix)[j][i];
                  }
              }

              Matrix<T> ret = Matrix<T>(mat_trans, this -> col, this -> row); 
              delete[] mat_trans;
              
              return ret;
          }

          Matrix<T> inverse() {
                Matrix<T> inv = Matrix<T>(this -> matrix_inv, this -> row, this -> col);
                return inv;
          }

          void show() {
            for(int i = 0 ; i < this -> row ; i++) {
                for(int j = 0 ; j < this -> col ; j++) {
                    cout<<(this -> matrix)[i][j]<<" ";
                }
                cout<<endl;
            }
          }

          triplet<int> dim() {
              return {this -> row, this -> col, 0};
          }

};


#endif
