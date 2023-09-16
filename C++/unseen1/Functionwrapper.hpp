
#pragma once 


template<typename>
class Function;

template<typename T>
class Function<bool(T,T)>
{
public:
    explicit Function(bool (*callable)(T arg, T arg2)): m_function(callable) {}
    bool operator()(T arg, T arg2)
    {
        return m_function(arg,arg2);   
    }    
      
private:
    bool (*m_function)(T arg, T arg2);
};