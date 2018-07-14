#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

#include "../Standerd.hpp"
#include "../Linkedlist.hpp"
#include "../Math.hpp"
#include "../Tools.hpp"
#include "../Type.hpp"
#include "../Matrix.hpp"
#include "../Cast.hpp"

template <typename T, typename L>
class LinearRegression {

    private:

        Matrix<T> beta;

    public:
        LinearRegression() {}

        void fit(Matrix<T> &X, Matrix<L> &Y) {
            auto dim_x = X.dim(), dim_y = Y.dim();
            dim_x.show();
            dim_y.show();
        }
};

#endif