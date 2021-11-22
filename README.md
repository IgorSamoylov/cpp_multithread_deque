# DEQUE_HM

Implementation of a double-ended queue for multithreading purpose, based on linked list. Deque has 2 mutex locks at front and back, what allow adding / removing nodes at the front and at the back independently. Collision of creating start node of the deque solving by start mutex and condition variable. Mutex locking in a one thread, who creates start node, which cause waiting on condition variable in another.   


![DequeHM schema](https://user-images.githubusercontent.com/81585628/142864786-df8939fc-1f04-4a78-88f1-d40baeafa204.jpg)
