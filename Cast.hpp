#ifndef CAST_HPP
#define CAST_HPP

#include "Standerd.hpp"
// #include "Type.hpp"

template <typename T>
class Cast {
    private:
        vector<char> valid_chars;
        function<T(string)> cast_function;
        char type = '_';

        bool contain(char arg) {
            bool ret = false;
            for(auto && item : valid_chars) {
                if(item == arg) {
                    ret = true;
                    break;
                }
            }
            return ret;
        }

        double string_to_double(string arg) const {
            return stod(arg.c_str());
        }

        int string_to_int(string arg) const {
            return stoi(arg.c_str());
        }

        long string_to_long(string arg) const {
            return stol(arg.c_str());
        }

        float string_to_float(string arg) const {
            return stof(arg.c_str());
        }

        void cfunc(T& val, string& str) {
            
            switch (type)
            {
                case 'i':
                    val = this -> string_to_int(str);
                    break;

                case 'd':
                    val = this -> string_to_double(str);
                    break;

                case 'l':
                    val = this -> string_to_long(str);
                    break;

                case 'f':
                    val = this -> string_to_float(str);
                    break;
            }
        } 
    
    public:

        Cast() {}

        Cast(initializer_list<char> vchars, function<T(string)> cfunc) {
            this -> valid_chars.reserve(vchars.size());
            for(auto && item : vchars) {
                this -> valid_chars.push_back(item);
            }
            this -> cast_function = cfunc;
        }

        Cast(int assci_begin, int assci_end, function<T(string)> cfunc) {
            this -> valid_chars.reserve(assci_end - assci_begin + 1);
            for(int item = assci_begin ; item <= assci_end ; item++) {
                this -> valid_chars.push_back(char(item));
            }
            this -> cast_function = cfunc;
        }

        Cast(initializer_list<char> vchars, string cfunc) {
            this -> valid_chars.reserve(vchars.size());
            for(auto && item : vchars) {
                this -> valid_chars.push_back(item);
            }
            this -> type = cfunc.back();
        }

        Cast(int assci_begin, int assci_end, string cfunc) {
            this -> valid_chars.reserve(assci_end - assci_begin + 1);
            for(int item = assci_begin ; item <= assci_end ; item++) {
                this -> valid_chars.push_back(char(item));
            }
            this -> type = cfunc.back();
        }

        ~Cast() {
            this -> valid_chars.clear();
        }

        void add_valid_char(char elt) {
            this -> valid_chars.push_back(elt);
        }

        T cast(string arg) {
            if(type != '_') {
                T val;
                this -> cfunc(val, arg);
                return val;
            }
            else 
                return this -> cast_function(arg);
        }

        bool valid(string arg) {
            for(auto && item : arg) {
                if(!this -> contain(item)) {
                    return false;
                }
            }
            return true;
        }
};

#endif