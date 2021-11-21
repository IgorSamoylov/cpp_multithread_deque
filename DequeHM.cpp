#include "DequeHM.h"

template <class T>
DequeHM<T>::DequeHM() {}


template <class T>
void DequeHM<T>::push_back(T input) {

	back_mutex.lock();
	
	Node<T>* new_node = new Node<T>(input);
	deque_size++;

	if (first_node == nullptr) {
		std::unique_lock<std::mutex> lk(wait_mutex);
		if (start_mutex.try_lock()) {
			first_node = new_node;
			last_node = new_node;
			back_mutex.unlock(); start_mutex.unlock();
			cv.notify_all();
			return;
		}
		else cv.wait(lk);
	}
	new_node->prev = last_node;
	last_node->next = new_node;
	last_node = new_node;

	back_mutex.unlock();
}

template<class T>
void DequeHM<T>::push_front(T input) {

	front_mutex.lock();

	Node<T>* new_node = new Node<T>(input);
	deque_size++;
	if (first_node == nullptr) {
		std::unique_lock<std::mutex> lk(wait_mutex);
		if (start_mutex.try_lock()) {
			first_node = new_node;
			last_node = new_node;
			front_mutex.unlock(); start_mutex.unlock();
			cv.notify_all();
			return;
		}
		else cv.wait(lk);
	}
	new_node->next = first_node;
	first_node->prev = new_node;
	first_node = new_node;

	front_mutex.unlock();
}

template<class T>
T& DequeHM<T>::pop_forward() {

	front_mutex.lock();

	T result;
	if (first_node != nullptr) {
		//result = std::move(first_node->val);
		result = first_node->val;
		Node<T>* new_first_node = first_node->next;
		delete(first_node);
		first_node = new_first_node;
		deque_size--;
	}
	else throw std::exception("Deque is empty!");

	front_mutex.unlock();

	return result;
}

template<class T>
T& DequeHM<T>::pop_back() {

	back_mutex.lock();

	T result;
	if (last_node != nullptr) {
		//result = std::move(last_node->val);
		result = last_node->val;
		Node<T>* new_last_node = last_node->prev;
		delete(last_node);
		last_node = new_last_node;
		deque_size--;
	}
	else throw std::exception("Deque is empty!");

	back_mutex.unlock();

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


