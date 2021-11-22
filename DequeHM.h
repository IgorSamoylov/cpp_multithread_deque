#pragma once
#include <mutex>
#include <atomic>

template <class T>
class Node {
public:
	T val;
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;
	Node(const T& input) : val(input) {};
};

template <class T>
class DequeHM {
	Node<T>* first_node = nullptr;
	Node<T>* last_node = nullptr;
	std::atomic_long deque_size = 0;
public:
	void push_back(const T& input);
	void push_front(const T& input);
	T pop_forward();
	T pop_back();
	std::atomic_bool is_empty();
	std::atomic_long size();
	
	DequeHM();
	~DequeHM();
private:
	std::mutex start_mutex;
	std::condition_variable cv;
	std::mutex wait_mutex;
	std::mutex front_mutex;
	std::mutex back_mutex;
};