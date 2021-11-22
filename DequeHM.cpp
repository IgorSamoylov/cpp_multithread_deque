#include "DequeHM.h"

template <class T>
DequeHM<T>::DequeHM() {}


template <class T>
void DequeHM<T>::push_back(T input) {

	std::lock_guard<std::mutex> guard(back_mutex);
	
	Node<T>* new_node = new Node<T>(input);
	deque_size++;

	if (first_node == nullptr) {
		
		if (start_mutex.try_lock()) {
			first_node = new_node;
			last_node = new_node;
			start_mutex.unlock();
			cv.notify_all();
			return;
		}
		else {
			std::unique_lock<std::mutex> lk(wait_mutex);
			cv.wait(lk);
		}
	}
	new_node->prev = last_node;
	last_node->next = new_node;
	last_node = new_node;
}

template<class T>
void DequeHM<T>::push_front(T input) {

	std::lock_guard<std::mutex> guard(front_mutex);

	Node<T>* new_node = new Node<T>(input);
	deque_size++;
	if (first_node == nullptr) {
		
		if (start_mutex.try_lock()) {
			first_node = new_node;
			last_node = new_node;
			start_mutex.unlock();
			cv.notify_all();
			return;
		}
		else {
			std::unique_lock<std::mutex> lk(wait_mutex);
			cv.wait(lk);
		}
	}
	new_node->next = first_node;
	first_node->prev = new_node;
	first_node = new_node;
}

template<class T>
T& DequeHM<T>::pop_forward() {

	std::lock_guard<std::mutex> guard(front_mutex);

	T result;
	if (first_node != nullptr) {
		result = std::move(first_node->val);
		//result = first_node->val;
		Node<T>* new_first_node = first_node->next;
		delete(first_node);
		first_node = new_first_node;
		deque_size--;
	}
	else throw std::exception("Deque is empty!");

	return result;
}

template<class T>
T& DequeHM<T>::pop_back() {

	std::lock_guard<std::mutex> guard(back_mutex);
	
	T result;
	if (last_node != nullptr) {
		result = std::move(last_node->val);
		//result = last_node->val;
		Node<T>* new_last_node = last_node->prev;
		delete(last_node);
		last_node = new_last_node;
		deque_size--;
	}
	else throw std::exception("Deque is empty!");

	return result;
}

template<class T>
long DequeHM<T>::size() {

	return deque_size;
}

template<class T>
bool DequeHM<T>::is_empty() {

	return deque_size == 0;
}


template<class T>
DequeHM<T>::~DequeHM() {
	// Cleaning node's chain if not empty
	if (deque_size > 0) {
		Node<T>* node = first_node;
		while (node != nullptr) {
			Node<T>* nextNode = node->next;
			delete(node);
			node = nextNode;
		}
	}
}


