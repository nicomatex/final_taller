#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>

template<class T>
std::list<T> DobleSegunda(std::list<T> &a,std::list<T> &b){
    std::list<T> result;
    for(auto it = a.begin(); it != a.end(); it++){
        result.push_back(*it);
        if(std::find(b.begin(),b.end(),*it) != b.end()){
            result.push_back(*it);
        }
        
    }
    return result;
}


int main(void){
    std::list<int> a = {1,2,3,4};
    std::list<int> b = {1,2};
    std::list<int> c = DobleSegunda(a,b);
    for(auto it: c){
        std::cout << it << std::endl;
    }
    return 0;
}
