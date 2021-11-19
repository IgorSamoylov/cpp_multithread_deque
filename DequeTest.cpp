
#include <iostream>
#include "DequeHM.h"
#include "DequeHM.cpp"
#include <thread>

using namespace std;


int main() {

    DequeHM<int>* dequeHM = new DequeHM<int>();

    auto push_back = [](DequeHM<int>& dequeHM) {
        for (int i = 0; i < 100; i++) {
            dequeHM.push_back(i);
        }
    };
    auto push_front = [](DequeHM<int>& dequeHM) {
        for (int i = 0; i < 100; i++) {
            dequeHM.push_forward(i * 10);
        }
    };
    auto pop_back = [](DequeHM<int>& dequeHM) {
        while (!dequeHM.is_empty()) {
            cout << dequeHM.pop_back() << " ";
        }
    };
    
    thread thread1(push_back, std::ref(*dequeHM));
    thread thread2(push_front, std::ref(*dequeHM));
    //thread thread3(pop_back, std::ref(*dequeHM));
    //thread thread4(push_front, std::ref(*dequeHM));
    thread1.detach();
    thread2.detach();
    this_thread::sleep_for(1000ms);
    //thread3.detach();
    //thread4.join();
    

    cout << "Deque Entry: " << endl;
    for (Node<int>* node = dequeHM->first_node; node != nullptr; node = node->next) {
         cout << node->val << " ";
    }
    cout << endl;

    delete(dequeHM);  
}

