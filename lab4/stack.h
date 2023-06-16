#ifndef __STACK_H__
#define __STACK_H__
#include <iostream>
#include <stdexcept>
using namespace std;
const int MAX_SIZE = 20;

template<class T>
class stack
{
    public:
        stack<T>()
        {
            size = 0;
        }

        void push(T val)
        {
            try
            {
                if(size >= MAX_SIZE)
                {
                    throw overflow_error("Called push on full stack.");
                }
                else
                {
                    data[MAX_SIZE - size - 1] = val;
                    size += 1;
                }
            }
            catch(overflow_error &excpt)
            {
                cout << excpt.what() << endl;
                exit(1);
            }
        }

        void pop()
        {
            try
            {
                if(empty())
                {
                    throw out_of_range("Called pop on empty stack.");
                }
                else
                {
                    size -= 1;
                }
            }
            catch(out_of_range &excpt)
            {
                cout << excpt.what() << endl;
                exit(1);
            }
        }

        void pop_two()
        {
            try
            {
                if(empty())
                {
                    throw out_of_range("Called pop on empty stack.");
                }
                else if(size == 1)
                {
                    throw out_of_range("Called pop_two on a stack of size 1.");
                }
                else
                {
                    size -= 2;
                }
            }
            catch(out_of_range &excpt)
            {
                cout << excpt.what() << endl;
                exit(1);
            }
        }

        T top()
        {
            try
            {
                if(empty())
                {
                    throw underflow_error("Called top on empty stack.");
                }
                else
                {
                    return data[MAX_SIZE - size];
                }
            }
            catch(out_of_range &excpt)
            {
                cout << excpt.what() << endl;
                exit(1);
            }
        }

        bool empty()
        {
            if(size == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    private:
        T data[MAX_SIZE];
        int size;
};

#endif