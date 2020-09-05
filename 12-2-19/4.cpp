/*
4) Escriba un programa que imprima por salida estándar los números entre 1 y 100, en orden
ascendente. Se pide que los números sean contabilizados por una variable global única y que
los pares sean escritos por un hilo mientras que los impares sean escritos por otro.
Contemple la correcta sincronización entre hilos y la liberación de los recursos utilizados.
*/

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>


int number;

class Printer{
    private:
        std::mutex m;
        std::condition_variable cv;
    public:
        void print_and_increment(bool even){
            std::unique_lock<std::mutex> l(m);
            while((number % 2 == 0) != even){
                cv.wait(l);
            }
            std::cout << number << std::endl;
            number++;
            cv.notify_all();
        }
};

void print_evens(int max, Printer& printer){
    while(number <= max){
        printer.print_and_increment(true);
    }
}

void print_odds(int max, Printer& printer){
    while(number <= max){
        printer.print_and_increment(false);
    }
}

int main(void){
    number = 1;
    Printer printer;
    std::thread t1(print_evens,100,std::ref(printer));
    std::thread t2(print_odds,100,std::ref(printer));
    t1.join();
    t2.join();
    return 0;
}