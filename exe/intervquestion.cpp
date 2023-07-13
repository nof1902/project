#include <unordered_map>
#include <vector>
#include <ostream>
#include <iostream>


void FindPath(std::unordered_map<char,char> &map)
{
    std::unordered_map<char,char> visited;
}

int main()
{
    std::unordered_map<char,char> path;

    path.insert({'x','y'});
    path.insert({'t','z'});
    path.insert({'h','x'});
    path.insert({'z','h'});

    std::vector<char>answer(4,0);
    
    FindPath(path);

    return 0;
}