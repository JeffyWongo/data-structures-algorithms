#include "Heap.h"
using namespace std;
#include <iostream>

Heap::Heap()
{
    numItems = 0;
}

void Heap::enqueue(PrintJob* job)
{
    if (numItems != MAX_HEAP_SIZE)
    {
        if(numItems == 0) // if empty
        {
            arr[numItems] = job;
            numItems++;
        }
        else
        {
            int currIndex = numItems;
            while(currIndex > 0 && arr[(currIndex-1) / 2]->getPriority() < job->getPriority()) // while within array and parent is less than input
            { // makes child node equal to parent node
                int parentIndex = (currIndex - 1) / 2;
                arr[currIndex] = arr[parentIndex];
                currIndex = parentIndex;
            }
            arr[currIndex] = job; // changes node's value at correct location
            numItems++;
        }
    }
}

void Heap::swap(int child, int parent)
{
    PrintJob* temp = arr[child];
    arr[child] = arr[parent];
    arr[parent] = temp;
}


void Heap::dequeue()
{
    if(numItems == 0)
    {
        cout << "Heap is empty" << endl;
        return;
    }
    else if(numItems == 1)
    {
        numItems--;
        trickleDown(0);
    }
    else
    {
        arr[0] = arr[numItems - 1];
        numItems--;
        trickleDown(0);
    }
}

PrintJob* Heap::highest() 
{
    if (numItems == 0) // if heap is empty return 0 else return highest priority
    { 
        return 0;
    }
    else 
    {
        return arr[0];
    }
}

void Heap::print() 
{
    if (numItems != 0) 
    {
        cout << "Priority: " << arr[0]->getPriority();
        cout << ", Job Number: " << arr[0]->getJobNumber();
        cout << ", Number of Pages: " << arr[0]->getPages();
    }
    else
    {
        cout << "Heap is empty" << endl;
    }
    cout << endl;
}

void Heap::trickleDown(int nodeIndex)
{ // nodeIndex is always going to start at 0
    int childIndex = 2 * nodeIndex + 1;

    while (childIndex < numItems)
    { // find max among children and parent
        PrintJob* value = arr[nodeIndex]; // storing parent node
        PrintJob* maxValue = value;
        int maxIndex = -1; // reset max location for each loop
        for(int i = 0; i < 2 && i + childIndex < numItems; i++) // checks all children and assigns max out of the children and parent nodes 
        {
            if(arr[i + childIndex]->getPriority() > maxValue->getPriority())
            {
                maxValue = arr[i + childIndex];
                maxIndex = i + childIndex;
            }
        }

        if(maxValue == value) // checks if heap is already correct
        {
            return;
        }

        else
        {
            swap(nodeIndex, maxIndex);
            nodeIndex = maxIndex;
            childIndex = 2 * nodeIndex + 1;
        }
    }
}
