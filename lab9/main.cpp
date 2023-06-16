#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000;

int Partition_midpoint(int numbers[], int i, int k);
void Quicksort_midpoint(int numbers[], int i, int k);
int Partition_medianOfThree(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);
void InsertionSort(int numbers[], int numbersSize);
int middle(int, int, int);


int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int[],int[],int[]);

int main(){
    srand(time(0));
    int arr1[NUMBERS_SIZE];// { 10, 2, 78, 4, 45, 32, 7, 11 };
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    fillArrays(arr1,arr2,arr3);
    
    //int i = 0;
    
    // cout << "UNSORTED: ";
    // for(i = 0; i < NUMBERS_SIZE; ++i) {
    //   cout << numbers[i] << " ";
    // }
    // cout << endl;
    //int t1 = time(0);
    clock_t Start = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    clock_t End = clock();
    cout<<"Time elapsed 1: "<<(End - Start)/CLOCKS_PER_MS<<endl;
    
    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1);
    End = clock();
    cout<<"Time elapsed 2: "<<(End - Start)/CLOCKS_PER_MS<<endl;
    
    Start = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    End = clock();
    cout<<"Time elapsed 3: "<<(End - Start)/CLOCKS_PER_MS<<endl;
    
    
    Start = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    End = clock();
    cout<<"Time elapsed 1: "<<(End - Start)/CLOCKS_PER_MS<<endl;
    
    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1);
    End = clock();
    cout<<"Time elapsed 2: "<<(End - Start)/CLOCKS_PER_MS<<endl;
    
    Start = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    End = clock();
    cout<<"Time elapsed 3: "<<(End - Start)/CLOCKS_PER_MS<<endl;
    
    // cout << "SORTED: ";
    // for(i = 0; i < NUMBERS_SIZE; ++i) {
    //   cout << numbers[i] << " ";
    // }
    // cout << endl;
   
    return 0;
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,100000);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int Partition_midpoint(int numbers[], int i, int k) {
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = numbers[midpoint];
   //pivot = numbers[i];
   
   l = i;
   h = k;
   
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while (numbers[l] < pivot) {
         ++l;
      }
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < numbers[h]) {
         --h;
      }
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
   int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition_midpoint(numbers, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort_midpoint(numbers, i, j);
   Quicksort_midpoint(numbers, j + 1, k);
   
   return;
}

int Partition_medianOfThree(int numbers[], int i, int k) {
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   //pivot = numbers[midpoint];
   
   pivot = middle(numbers[i],numbers[k],numbers[midpoint]);
   //pivot = median3(numbers,i,k);
   
   l = i;
   h = k;
   
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while (numbers[l] < pivot) {
         ++l;
      }
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < numbers[h]) {
         --h;
      }
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = numbers[l];
         numbers[l] = numbers[h];
         numbers[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
   int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition_medianOfThree(numbers, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort_medianOfThree(numbers, i, j);
   Quicksort_medianOfThree(numbers, j + 1, k);
   
   return;
}

int middle(int a, int b, int c){
    if(a> min(b,c) && a < max(b,c)){
        return a;
    }
    else if(b> min(a,c) && b < max(a,c)){
        return b;
    }
    else{
        return c;
    }
}


void InsertionSort(int numbers[], int numbersSize) {
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap
   
   for (i = 1; i < numbersSize; ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && numbers[j] < numbers[j - 1]) {
         
         // Swap numbers[j] and numbers[j - 1]
         temp = numbers[j];
         numbers[j] = numbers[j - 1];
         numbers[j - 1] = temp;
         --j;
      }
   }
   
   return;
}