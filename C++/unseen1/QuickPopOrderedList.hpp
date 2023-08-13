#pragma once 
#include <pthread.h>

#include "Functionwrapper.hpp"

template<typename T>
class Node
{
public:
   Node(T *value);
   Node<T> *GetNextNode();
   T GetValue();
   void SetNextNode(Node<T> *next);
   void SetValue(Node<T> *next);
private:
    T *m_value;
    Node<T> *m_next;
};

/* singelton? */
template<typename T>
class QuickPopOrderedList
{   
public:
    QuickPopOrderedList(Function<bool(T,T)> &comperfunc);
    ~QuickPopOrderedList();
    size_t GetSize();
    bool IsEmpty();
    T Pop();
    void Push(T *value);
    void PrintList();

private:
    QuickPopOrderedList(const QuickPopOrderedList<T> &other); // no copy constructor
    QuickPopOrderedList& operator =(const QuickPopOrderedList<T> &other); // no assinment operator
    void InsertRigthPlace(Node<T> *new_node);
    Function<bool(T,T)> &m_comperfunc;
    Node<T> *m_head;
    size_t m_size;
    pthread_mutex_t m_guard;
    pthread_mutex_t m_guard2;
};

/* *******************************Node*************************************** */
template<typename T>
Node<T>::Node(T *value): m_value(value), m_next(NULL)
{}

template<typename T>
Node<T> *Node<T>::GetNextNode()
{
    return m_next;
}

template<typename T>
T Node<T>::GetValue()
{
    return *m_value;
}

template<typename T>
void Node<T>::SetNextNode(Node<T> *next)
{
    m_next = next;
}

template<typename T>
void Node<T>::SetValue(Node<T> *next)
{
    m_value = next->GetValue();
}

/* **************************QuickPopOrderedList***************************** */
template<typename T>
QuickPopOrderedList<T>::QuickPopOrderedList(Function<bool(T,T)> &comperfunc): 
m_comperfunc(comperfunc), m_head(NULL) ,m_size(0)
{
    pthread_mutex_init(&m_guard,NULL);
    pthread_mutex_init(&m_guard2,NULL);
}

template<typename T>
QuickPopOrderedList<T>::~QuickPopOrderedList()
{
    while(m_head)
    {
        Node<T> *node = m_head;
        m_head = m_head->GetNextNode();
        delete node;
    }
    pthread_mutex_destroy(&m_guard);
}

template<typename T>
T QuickPopOrderedList<T>::Pop()
{
    pthread_mutex_lock(&m_guard);
    // if(IsEmpty())
    // {
    //     pthread_mutex_unlock(&m_guard);
    //     return -1;
    // }
    Node<T> *node_to_erase = m_head;
    m_head = m_head->GetNextNode();
    int ret_val = node_to_erase->GetValue();
    delete node_to_erase;
    --m_size;
    pthread_mutex_unlock(&m_guard);
    return ret_val;
}

template<typename T>
void QuickPopOrderedList<T>::Push(T *value)
{
    Node<T> *new_node = new Node<T>(value);
    pthread_mutex_lock(&m_guard);
    if(m_head == NULL || 
            true == (m_comperfunc)(new_node->GetValue(), m_head->GetValue()))
    {
        new_node->SetNextNode(m_head);
        m_head = new_node;
    }
    else
    {
        InsertRigthPlace(new_node);
    }
    ++m_size;
    pthread_mutex_unlock(&m_guard);
}

template<typename T>
size_t QuickPopOrderedList<T>::GetSize()
{
    return m_size;
}

template<typename T>
bool QuickPopOrderedList<T>::IsEmpty()
{
    //return !__atomic_load_n(&m_size,__ATOMIC_SEQ_CST);
    return m_size == 0;
}

template<typename T>
void QuickPopOrderedList<T>::InsertRigthPlace(Node<T> *new_node)
{
    Node<T> *newN = new_node;
    Node<T> *curr = m_head;
    Node<T> *prev = NULL;

    while(curr && false == (m_comperfunc)(newN->GetValue(), curr->GetValue()))
    {
        prev = curr;
        curr = curr->GetNextNode();
    }

    if(curr)
    {
        new_node->SetNextNode(prev->GetNextNode());
        prev->SetNextNode(new_node);
    }

    else
    {
        new_node->SetNextNode(curr);
        prev->SetNextNode(new_node);
    }
}

template<typename T>
void QuickPopOrderedList<T>::PrintList()
{
    Node<T> *curr = m_head;
    while(curr)
    {
        std::cout << curr->GetValue() << std::endl;
        curr = curr->GetNextNode();
    }
}

/* 

    while(next_curr->GetNextNode() != NULL)
    {
        
        if(false  == (m_comperfunc)(curr->GetValue(), next_curr->GetValue()))
        {
            if(curr == m_head)
            {
                m_head = next_curr;
            }
            SwapNodes(curr, next_curr);
            
            next_curr = curr;
            curr =  curr->GetNextNode();
            continue;
        }

        curr = next_curr;
        next_curr = next_curr->GetNextNode();
    }

Node<T> *prev = m_head;
    Node<T> *curr = curr->GetNextNode();

    while(next_curr->GetNextNode() != NULL)
    {
        
        if(false  == (m_comperfunc)(curr->GetValue(), next_curr->GetValue()))
        {
            if(curr == m_head)
            {
                m_head = next_curr;
            }
            SwapNodes(curr, next_curr);
            
            next_curr = curr;
            curr =  curr->GetNextNode();
            continue;
        }

        curr = next_curr;
        next_curr = next_curr->GetNextNode();
    }




 */