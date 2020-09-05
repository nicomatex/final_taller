/*
3) Escriba un programa que imprima por salida estándar los números entre 1 y 100, en orden
ascendente. Se pide que los números sean contabilizados por una variable global única y que
los pares sean escritos por un hilo mientras que los impares sean escritos por otro.
Contemple la correcta sincronización entre hilos y la liberación de los recursos utilizados.
*/


#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

int num;

class Printer{
    private:
        std::mutex m;
        std::condition_variable cv;
    public:
        bool print_num(bool even, int max){
            std::unique_lock<std::mutex> l(m);
            while((num % 2 == 0) != even){
                cv.wait(l);
            }
            std::cout << num << std::endl;
            num++;
            cv.notify_all();
            return num <= max;
        }
};

void print_evens(int max, Printer& printer){
    bool continue_printing = true;
    while(continue_printing){
        continue_printing = printer.print_num(true,max);
    }
}

void print_odds(int max, Printer& printer){
    bool continue_printing = true;
    while(continue_printing){
        continue_printing = printer.print_num(false,max);
    }
}

int main(void){
    num = 1;
    Printer printer;
    std::thread t1(print_evens,100,std::ref(printer));
    std::thread t2(print_odds,100,std::ref(printer));
    t1.join();
    t2.join();
    return 0;
}