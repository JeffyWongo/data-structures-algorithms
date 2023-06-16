#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index)
{
    unsigned minIndex = index;
    for(unsigned i = index; i<vals.size(); i++)
    {
        if(vals.at(minIndex) > vals.at(i))
        {
            minIndex = i;
        }
    }
    return minIndex;
}

template<typename T>
vector<T> selection_sort(vector<T> &vals)
{
    for(unsigned i = 0; i<vals.size(); i++)
    {
        unsigned min = min_index(vals,i);
        T temp = vals.at(min);
        vals.at(min) = vals.at(i);
        vals.at(i) = temp;
    }
    return vals;
}

int main()
{
    vector<int>vals = {2,9,3,1,4};
    selection_sort(vals);
    for(unsigned i = 0; i < vals.size(); i++)
    {
        cout << vals.at(i) << endl;
    }
    return 0;
}