#include "IntList.h"

int main()
{
    IntList list = IntList();
	
	cout << "Testing push_back and push_front" << endl;
	list.push_back(1);
	list.push_back(2);
	list.push_front(3);
	list.push_front(4);
	
	cout << "Printing list" << endl;
    cout << list << endl;
	cout << "In reverse: " << endl;
	list.printReverse();
	cout << endl;
	
	cout << "Testing pop_back and pop_front" << endl;
	list.pop_back();
	list.pop_front();
	
	cout << "Printing list" << endl;
    cout << list << endl;
	cout << "In reverse: " << endl;
	list.printReverse();
	cout << endl;

    cout << "Testing empty list" << endl;
    list.pop_front();
    list.pop_front();
    cout << list << endl;
    cout << "Printing reverse empty list" << endl;
    list.printReverse();
    cout << endl;
	return 0;
}