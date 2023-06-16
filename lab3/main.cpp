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

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template<typename T>
T getElement(vector<T> vals, int index)
{
    return vals.at(index);
}

int main(){

    //Part B
    vector<string> test2 {"hello", "cs10c", "polarize", "polarbear", "tiktok"};
    vector<int> test1 {14, 5, 66, 3, 1234, 55};

    selection_sort(test2);
    for(int i = 0; i < test2.size(); i++)
    {
        cout << test2.at(i) << " ";
    }
    cout << endl;

    selection_sort(test1);
    for(int i = 0; i < test1.size(); i++)
    {
        cout << test1.at(i) << " ";
    }

     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     unsigned index;
     int numOfRuns = 10;
     cin.exceptions(ios::failbit);
     while(--numOfRuns >= 0){
         try
         {
            cout << "Enter a number: " << endl;
            cin >> index;
            if(index >= vals.size())
            {
                throw out_of_range("out of range exception occured");
            }
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
         }
         catch(out_of_range& excpt)
         {
            cout << excpt.what() << endl;
         }
         catch(ios_base::failure& excpt)
         {
            cout << "Invalid input" << endl;
            break;
         }
    }
    return 0;
}

// T getElement(vector<T> vals, int index): Passes in a vector of type T (T could be string, double or int) and an index of type int. 
// The function returns the element located at the index of the vals. 
// You should write up a try catch block in main function so that when the index is out of the range of the vector, 
// the "std::outofrange" exception will be caught by the catch (const std::outofrange& excpt). 
// Once the exception is caught, it should output "out of range exception occured" followed by a new line.