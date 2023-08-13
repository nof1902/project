#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include "Functionwrapper.hpp"
#include "QuickPopOrderedList.hpp"

#define NUM_OF_THREADS 2
#define SIZE_OF_LIST 10

//const size_t NUM_OF_THREADS = 2;
//const size_t SIZE_OF_LIST = 10;

bool CompareInts(int new_value, int old_value);
void *Producer(void *numoftheads);
void *Consumer(void *numoftheads);

int data[SIZE_OF_LIST] = {0};
int answerArray[SIZE_OF_LIST] = {0};
Function<bool(int,int)> comparison_fn(&CompareInts);
QuickPopOrderedList<int> quickPopOrderedList(comparison_fn);
pthread_mutex_t regulator;
pthread_mutex_t regulator2;
int g_i = 0;
int g_j = 0;

int main()
{
    pthread_t producers[NUM_OF_THREADS] = {0};
    pthread_t consumers[NUM_OF_THREADS] = {0};
    pthread_mutex_init(&regulator,NULL);
    pthread_mutex_init(&regulator2,NULL);

    for(size_t i = 0; i < NUM_OF_THREADS; ++i)
    {
        while(pthread_create(producers + i,NULL,Producer,(void *)i))
        {
            perror("pthread_create");
        }
    }

    for(size_t i = 0; i < NUM_OF_THREADS; ++i)
    {     
       if(pthread_join(producers[i], 0))
       {
            printf("fail");
       }
    }

    for(size_t i = 0; i < NUM_OF_THREADS; ++i)
    {
        while(pthread_create(consumers + i,NULL,Consumer,(void *)i))
        {
           perror("pthread_create"); 
        }
    }

    for(size_t i = 0; i < NUM_OF_THREADS; ++i)
    {
       if(pthread_join(consumers[i], 0))
       {
            printf("fail");
       }
    }

    for(size_t i = 0; i < SIZE_OF_LIST; ++i)
    {
        printf("%d\n",answerArray[i]);
    }

    pthread_mutex_destroy(&regulator);
    pthread_mutex_destroy(&regulator2);
    return 0;
}

bool CompareInts(int new_value, int old_value)
{
    return new_value >= old_value;
}

void *Producer(void *numoftheads)
{
    (void)numoftheads;
    
    while(g_j < SIZE_OF_LIST)
    {
        pthread_mutex_lock(&regulator);
        data[g_j] = rand() % 2100;
        quickPopOrderedList.Push(data + g_j);
        ++g_j;
        pthread_mutex_unlock(&regulator);
    }

    return NULL;
}

void *Consumer(void *numoftheads)
{
    (void)numoftheads;
    //pthread_mutex_lock(&regulator);
    while(quickPopOrderedList.IsEmpty() == false)
    {
        pthread_mutex_lock(&regulator);
        answerArray[g_i] = quickPopOrderedList.Pop();
        ++g_i;
        pthread_mutex_unlock(&regulator);
    } 

    return NULL;
}

// void *Consumer(void *numoftheads)
// {
//     (void)numoftheads;

//     for(int i = 0; !quickPopOrderedList.IsEmpty(); ++i)
//     {
//         pthread_mutex_lock(&regulator);
//         answerArray[i++] = quickPopOrderedList.Pop();
//         pthread_mutex_unlock(&regulator);
//     }

//     return NULL;
// }



