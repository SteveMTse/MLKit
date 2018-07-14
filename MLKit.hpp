#ifndef MLKIT_HPP
#define MLKIT_HPP

#include "Standerd.hpp"
#include "Linkedlist.hpp"
#include "Math.hpp"
#include "Tools.hpp"
#include "Type.hpp"
#include "Matrix.hpp"
#include "Cast.hpp"

template<typename T, typename L>
class generic_model {
    protected:
        int a;
    public:
                
        void fit(Matrix<T>& X, Matrix<L>& Y) {}

        Matrix<L> predict(Matrix<T>& unseen) {}
};

template <typename T>
Matrix<T> data_generator(const string filename, const char splitter, Cast<T> cast, int begin = 0, int size = -1) {
    ifstream data;
    int row = 0, col = size;
    int id_row = -1, index = 0;
    Matrix<T> ret;
    Linkedlist<T> data_buffer;
    String buffer = "";
    data.open(filename);

    // auto _ = readline(data, buffer);
    // buffer.split<T>(data_buffer, cast, begin, size);
    // data_buffer.show();
    // cout<<data_buffer.size()<<endl;

    while(readline(data, buffer)) {
        row ++;
        buffer.split<T>(data_buffer, cast, begin, size);
    }

    ret.set_dim(row, col);
    for(auto i = data_buffer.begin() ; i != NULL ; i = i -> next) {
        if(index % size == 0) {
            id_row ++;
        }
        ret[id_row][index % size] = i -> content;
        index++;
    }

    data.close();
    return ret;
}


#endif