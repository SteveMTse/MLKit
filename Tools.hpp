#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "Standerd.hpp"
#include "Type.hpp"

template <typename T>
void array_initializer(T** &array, int row, int col, T value) {
    array = new T*[row];
    for(int i = 0 ; i < row ; i++) {
        array[i] = new T[col];
        for(int j = 0 ; j < col ; j++) {
            array[i][j] = value;
        }
    }
}

template <typename T>
void array_print(T** &array, int row, int col) {
  for(int i = 0 ; i < row ; i++) {
      for(int j = 0 ; j < col ; j++) {
          cout<<array[i][j]<<" ";
      }
      cout<<endl;
  }
}

template <typename T>
void vector_print(vector<T>& arg, double precision = 5) {
    // cout.precision(5);
    cout.precision(precision);
    for(auto && item : arg) {
        cout<<fixed<<item<<", ";
    }
    cout<<endl;
}

bool readline(ifstream& data, String & arg) {
    string buff = "";
    bool ret = false;
    if(getline(data, buff)) {
        arg = buff;
        ret = true;
    }
    else {
        ret = false;
    }
    return ret;
}

template <typename T>
vector<T> strlist_to_numlist(vector<String> & arg) {
    vector<T> ret;
    ret.reserve(arg.size());
    for(auto & item : arg) {
        auto info = item.to_number();
        if(info.second) {
            ret.push_back(T(info.first));
        }
    }
    return ret;
}

template <typename T>
T sum(vector<T> & arg, int begin = 0, int end = -1) {
    T ret = arg[begin];
    if(end == -1) {
        end =arg.size() - 1;
    }
    if(begin < 0 || begin >= arg.size() || end < 0 || end >= arg.size() || begin > end) {
        begin = 0;
        end = arg.size() - 1;
    }
    for(int i = begin + 1 ; i <= end ; i++) {
        ret += arg[i];
    }
    return ret;
}

template <typename T>
T sum(initializer_list<T> arg, int begin = 0, int end = -1) {
    T ret;
    int assigned = false;
    int index = 0;
    if(end == -1) {
        end =arg.size() - 1;
    }
    if(begin < 0 || begin >= arg.size() || end < 0 || end >= arg.size() || begin > end) {
        begin = 0;
        end = arg.size() - 1;
    }
    for(auto && item : arg) {
        if(index >= begin && index <= end) {
            if(!assigned) {
                ret = item;
                assigned = true;
            }
            else {
                ret += item;
            }
        }
        index ++;
    }
    return ret;
}

#endif
