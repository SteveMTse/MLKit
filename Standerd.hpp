#ifndef STANDERD_HPP
#define STANDERD_HPP

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <thread>
#include <vector>
#include <utility>
#include <functional>
#include <exception>
#include <stdexcept>

using namespace std;

template <typename A, typename B = A, typename C = B>
struct triplet {
    A first;
    B second;
    C third;

    triplet() {}

    triplet(A arg1, B arg2, C arg3) {
        first = arg1;
        second = arg2;
        third = arg3;
    }

    void show() {
        cout<< "First: " << first << ", Second: " << second << ", Third: " << third << endl;
    }
};

#endif