#include <list>

template <class T>
std::list<T> Suprimir(std::list<T> a,std::list<T> b){
    std::list<T> final_list;
    for(auto i = a.begin(); i != a.end(); i++){
        auto item = std::find(b.begin();b.end();*i);
        if(item == b.end()){
            final_list.push_back(*i);
        }
    }
    return resultado;
}