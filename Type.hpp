#ifndef TYPE_HPP
#define TYPE_HPP

#include "Standerd.hpp"
#include "Linkedlist.hpp"
#include "Cast.hpp"

class String {

    private:

        string str = "";

    public:

        String() {}
        
        String(string arg) {
            this -> str = arg;
        }

        String(const char* arg) {
            this -> str = string(arg);
        }

        ~String() {
            this -> str.clear();
        }

        void operator= (const char * arg) {
            this -> str = string(arg);
        }

        void operator= (string& arg) {
            this -> str = arg;
        }

        void operator= (string&& arg) {
            this -> str = arg;
        }

        void operator+= (const char * arg) {
            (this -> str) += string(arg);
        }

        void operator+= (const char arg) {
            (this -> str) += arg;
        }

        char operator[] (const int index) {
            return (this -> str)[index];
        }

        const char* c_str() {
            return (this -> str).c_str();
        }

        const string o_str() {
            return this -> str;
        }

        size_t length() {
            return (this -> str).size();
        }

        bool empty() {
            return (this -> str).empty();
        }

        string content() const {
            return this -> str;
        }

        string::iterator begin() {
            return (this -> str).begin();
        }

        string::iterator end() {
            return (this -> str).end();
        }

        void clear() {
            (this -> str).clear();
        }

        vector<String> split(int size = -1, char splitter = ' ') {
            String buffer = "";
            vector<String> ret;
            ret.reserve(((size != -1) ? size : (this -> str).size() / 2));
            for(auto && item : this -> str) {
                if(size != -1 && ret.size() == size) {
                    buffer.clear();
                    break;
                }
                if(item != splitter) {
                    buffer += item;
                }
                else {
                    ret.push_back(buffer);
                    buffer.clear();
                    buffer = "";
                }
            }
            if(((size != -1 && ret.size() < size) || size == -1) && buffer.length() != 0) {
                ret.push_back(buffer);
            }
            return ret;
        }

        template <typename T>
        void split(Linkedlist<T>& storage, Cast<T> cast, int begin = 0, int size = -1, char splitter = ' ') {
            String buffer = "";
            int index = 0;
            for(auto && item : this -> str) {
                if(size != -1 && index == begin + size) {
                    buffer.clear();
                    break;
                }
                if(item != splitter) {
                    buffer += item;
                }
                else {
                    if(index >= begin) storage.push_back(cast.cast(buffer.o_str()));
                    buffer.clear();
                    index++;
                }
            }
            if(((size != -1 && index < begin + size) || size == -1) && buffer.length() != 0) {
                if(cast.valid(buffer.o_str())) storage.push_back(cast.cast(buffer.o_str()));
            }
        }


        // Frist := Number, Second := is number? Third := is a double;
        triplet<double, bool> to_number() {
            triplet<double, bool, bool> ret = {0.0, true, false};
            double factor = 0.1;
            for(auto && item : this -> str) {
                if(isdigit(item)) {
                    if(ret.third) {
                        ret.first += (factor * int(item - '0'));
                        factor *= 0.1;
                    }
                    else {
                        ret.first *= 10.0;
                        ret.first += int(item - '0');
                    }
                }
                else if(item == '.' && ret.third == false) {
                    ret.third = true;
                }
                else {
                    ret.first = 0.0;
                    ret.second = false;
                    ret.third = false;
                    break;
                }
            }
            return ret;
        }

        friend ostream& operator<<(ostream& os, const String& arg);
};

ostream& operator<<(ostream& os, const String& arg) { 
    os << arg.content();
    return (os);
}

#endif