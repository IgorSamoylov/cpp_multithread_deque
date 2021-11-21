#pragma once
#include <mutex>
#include <atomic>

template <class T>
class Node {
public:
	T val;
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;
	Node(T input) : val(input) {};
};

template <class T>
class DequeHM {
public:
	Node<T>* first_node = nullptr;
	Node<T>* last_node = nullptr;
	std::atomic_long deque_size = 0;
public:
	void push_back(T input);
	void push_front(T input);
	T& pop_forward();
	T& pop_back();
	bool is_empty();
	long size();
	
	DequeHM();
	~DequeHM();
private:
	std::mutex start_mutex;
	std::mutex front_mutex;
	std::mutex back_mutex;
};