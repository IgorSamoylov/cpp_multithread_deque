
#include <iostream>
#include "DequeHM.h"
#include "DequeHM.cpp"
#include <thread>
#include <chrono>

using namespace std;


int main() {

    DequeHM<int>* dequeHM = new DequeHM<int>();
    double elapsed_time1 = 0.0, elapsed_time2 = 0.0;

    auto push_back = [&elapsed_time1](DequeHM<int>& dequeHM) {
        //auto start = chrono::system_clock::now();
        for (int i = 0; i < 100; i++) {
            dequeHM.push_back(i);
        }
        //auto end = chrono::system_clock::now();
        //chrono::duration<double> time = end - start;
        //elapsed_time1 = time.count();

    };
    auto push_front = [](DequeHM<int>& dequeHM) {
        for (int i = 0; i < 100; i++) {
            dequeHM.push_front(i * 10);
        }
    };
    auto pop_back = [&elapsed_time2](DequeHM<int>& dequeHM) {
        //auto start = chrono::system_clock::now();
        while (!dequeHM.is_empty()) {
            cout << dequeHM.pop_back() << " ";
            //dequeHM.pop_back();
        }
        //auto end = chrono::system_clock::now();
        //chrono::duration<double> time = end - start;
        //elapsed_time2 = time.count();
    };
    
    
    thread thread1(push_back, std::ref(*dequeHM)); thread1.detach();
    thread thread2(push_front, std::ref(*dequeHM)); thread2.detach();
    this_thread::sleep_for(3000ms);
    thread thread3(pop_back, std::ref(*dequeHM)); thread3.join();
    //thread thread4(push_front, std::ref(*dequeHM)); thread4.join();
    
    //cout << "Elapsed Time 1 " << elapsed_time1 << endl;
    //cout << "Elapsed Time 2 " << elapsed_time2 << endl;
    /*cout << "Deque Entry: " << endl;
    for (Node<int>* node = dequeHM->first_node; node != nullptr; node = node->next) {
         cout << node->val << " ";
    }
    cout << endl;
    */
    delete(dequeHM);  
}

