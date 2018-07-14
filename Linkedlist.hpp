#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Standerd.hpp"

template <typename T>
struct Node {
    T content;
    Node<T>* previous;
    Node<T>* next;

    Node(T Element) {
        content = Element;
        previous = NULL;
        next = NULL;
    }
};

template <typename T>
class Linkedlist {
    private:
        size_t number_of_item = 0;
        Node<T>* head = NULL;
        Node<T>* tail = NULL;

        Node<T>* iterator(int index) {
            // cout<< "Index "<< index <<endl;
            if(index < 0 || index >= this -> number_of_item) {
                return NULL;
            }
            if(index == 0) return this -> head;
            if(index == this -> number_of_item - 1) return this -> tail;
            Node<T>* ret = this -> head;
            int counter = 0;
            while(ret != NULL && counter < index) {
                ret = ret -> next;
                counter ++;
            }
            return ret;
        }
    
    public:

        Linkedlist() {}

        Linkedlist(initializer_list<T> arg) {
            for(auto && item : arg) {
                this -> push_back(item);
            }
        }

        ~Linkedlist() {
            Node<T>* item = this -> head;
            this -> tail = NULL;
            while(item != NULL) {
                this -> head = (head) -> next;
                delete item;
                item = this -> head;
            }
            number_of_item = 0;
        }

        size_t size() {
            return this -> number_of_item;
        }

        T& peek_front() {
            return this -> head -> content;
        }

        T& peek_back() {
            return this -> tail -> content;
        }

        bool empty() {
            return (this -> number_of_item > 0) ? false : true; 
        }

        void push_back(T element) {
            this -> add(element, this -> number_of_item);
        }

        void push_front(T element) {
            this -> add(element, 0);
        }

        void pop_front() {
            this -> remove(0);
        }

        void pop_back() {
            this -> remove(this -> number_of_item - 1);
        }

        T& operator[] (const int index) {
            try {
                if(index < 0 || index >= this -> number_of_item || this -> head == NULL || this -> tail == NULL) {
                    throw out_of_range("Out Of Range");
                }
                else {
                    if(index == 0) {
                        return (this -> head) -> content;
                    }
                    else if(index == this -> number_of_item - 1) {
                        return (this -> tail) -> content;
                    }
                    else {
                        Node<T>* tmp = this -> iterator(index);
                        return tmp -> content;
                    }
                }
            }
            catch(const out_of_range& e) {
                cerr << e.what() << '\n';
            }
            
        }

        void add(T element, const int index) {
            Node<T>* tmp = NULL;
            Node<T>* prev = NULL;
            Node<T>* node = new Node<T>(element);
            if(number_of_item == 0) {
                this -> head = node;
                this -> tail = node;
            }
            else if(index >=0 && index <= this -> number_of_item - 1) {
                tmp = this -> iterator(index);
                // cout<<tmp -> content << endl;
                prev = (tmp != NULL) ? tmp -> previous : NULL;
                if(prev == NULL) {
                    node -> next = this -> head;
                    this -> head -> previous = node;
                    this -> head = node;
                }
                else {
                    prev -> next = node;
                    node -> previous = prev;
                    node -> next = tmp;
                    tmp -> previous = node;
                }
            }
            else {
                this -> tail -> next = node;
                node -> previous = this -> tail;
                this -> tail = node;
            }
            this -> number_of_item ++;
            node = NULL;
            tmp = NULL;
            prev = NULL;
        }

        Node<T>* begin() {
            return this -> head;
        }

        Node<T>* end() {
            return this -> tail;
        }

        void remove(const int index) {
            try
            {
                Node<T>* tmp = NULL;
                Node<T>* prev = NULL;
                Node<T>* nt = NULL;
                if(index < 0 && index >= this -> number_of_item) {
                    throw out_of_range("Out of range!");
                }
                else {
                    tmp = this -> iterator(index);
                    // cout<<tmp ->content <<endl;
                    prev = (tmp != NULL) ? tmp -> previous : NULL;
                    nt = (tmp != NULL) ? tmp -> next : NULL;   
                    if(prev != NULL) {
                        // cout<<"Prev: " << prev -> content <<endl;
                        prev -> next = nt;
                    }
                    else {
                        this -> head = nt;
                    }
                    if(nt != NULL) {
                        // cout<<"Next: " << nt -> content <<endl;
                        nt -> previous = prev;
                    }
                    else {
                        this -> tail = prev;
                    }
                    tmp -> next = NULL;
                    tmp -> previous = NULL;
                    delete tmp;
                    tmp = NULL;
                    prev = NULL;
                    nt = NULL;
                    this -> number_of_item --;
                }
            }
            catch(out_of_range& e)
            {
                cerr << e.what() << '\n';
            }
        }

        void show() {
            for(Node<T>* item = this -> head ; item != NULL ; item = item -> next) {
                cout << item -> content << ", ";
            }
            cout<<endl;
        }
};

#endif