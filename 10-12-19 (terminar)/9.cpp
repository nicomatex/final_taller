/*
9) Implemente una función C++ denominada Sacar que reciba dos listas de elementos y
devuelva una nueva lista con los elementos de la primera que no están en la segunda:
std::list<T> Sacar(std::list<T> a,std::list<T> b);
*/
#include <list>
#include <algorithm>

template<class T>
std::list<T> Sacar(std::list<T> &a, std::list<T> &b){
    std::list<T> result;
    for(auto item:a){
        if(std::find(b.begin(),b.end(),item) == b.end()){
            result.push_back(item);
        }
    }
    return result;
}


