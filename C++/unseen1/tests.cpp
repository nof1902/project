#include <ostream>
#include <iostream>
#include <string>
#include <vector>

#include "Functionwrapper.hpp"
#include "QuickPopOrderedList.hpp"

#define SIZE_OF_LIST 10
#define NUM_OF_THREADS 4

bool CompareInts(int new_value, int old_value)
{
    return new_value >= old_value;
}

int main()
{
    Function<bool(int,int)> comparison_fn(&CompareInts);
    QuickPopOrderedList<int> quickPopOrderedList(comparison_fn);
    int arr[SIZE_OF_LIST] = {0};

    pthread_t thread_id[NUM_OF_THREADS] = {0};

    for(int i = 0; i < NUM_OF_THREADS; ++i)
    {
        while(pthread_create(thread_id + i,NULL,SumOfDivisors,(void *)))
        {
            
        }
    }

    for(int i = 0; i < NUM_OF_THREADS; ++i)
    {
        arr[i] = rand() % 2000;
        quickPopOrderedList.Push(arr + i);
        std::cout << arr[i] << std::endl;
    }

    std::cout << "sizeof list : " << quickPopOrderedList.GetSize() << std::endl;

    while(quickPopOrderedList.GetSize() > 0)
    {
        std::cout << quickPopOrderedList.Pop() << std::endl;   
    }

    for(int i = 0; i < NUM_OF_THREADS; ++i)
    {
       if(pthread_join(thread_id[i], 0))
       {
            printf("fail");
       }
    }

    return 0;
}