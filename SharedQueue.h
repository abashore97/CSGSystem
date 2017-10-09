/*
	Abigail Bashore
	March 13, 2017
	Homework8
	SharedQueue Implementation
*/

#ifndef __Lab14__SharedQueue__
#define __Lab14__SharedQueue__

#include <mutex>
#include <iostream>
template <typename T>
class SharedQueue {
public:
  SharedQueue();
  ~SharedQueue();
  
    /*
     These declarations mean that we do NOT get the automatically
     defined copy/copy-assign functions.  If you try to call one
     by copying the queue, you'll get a compiler error.
     
     This is a common technique for things that are uncopyable (like std::thread and std::mutex, for example).
     
     We really DO want a destructor, so cheating at the
     rule of 3 here makes sense here.
     */
    SharedQueue(const SharedQueue<T>&) = delete;
    SharedQueue<T>& operator=(const SharedQueue<T>&) = delete;

    
  //Return true if the queue is empty
  bool isEmpty();
  
  //Enqueue the next item at the tail of the queue.
  void Add(T value);
  
  //Dequeue the next queue element and store it in "item" variable.  The function returns false if the queue is empty and no item can be retrieved.
  bool Remove(T &item);
  void Print();
private:
  struct QueueItem {
    T item;
    QueueItem *next;
	QueueItem(T v, QueueItem * n) :item(v), next(n) {}

	T getItem() const {
		return this->item;
	}
	
	QueueItem* getNext() const {
		return next;
	}

	void PrintQueueItem() {
		std::cout << "(" << item << ")" << " ";
	}

  };
  QueueItem * head;
  QueueItem * tail;
  std::mutex m;
};

template<typename T> 
SharedQueue<T>::SharedQueue() :head(nullptr), tail(nullptr) {}

template<typename T>
SharedQueue<T>::~SharedQueue() {
	QueueItem * current = head;
	while (current != nullptr) {
		current = current->next;
		delete head;
		head = current;
	}
	head = nullptr;
	tail = nullptr;

}

template <typename T> 
bool SharedQueue<T>::isEmpty(){
	if ((head == nullptr) && (tail == nullptr)) {
		return true;
	}
	return false;
}

template <typename T>
void SharedQueue<T>::Add(T value) {
	
	QueueItem *x = new QueueItem(value, nullptr);

	m.lock();
	if (isEmpty()) {
		head = x;
		tail = x;
		
	}

	else {
		tail->next = x;
		tail = x;

		
	}
	m.unlock();

}

template <typename T>
bool SharedQueue<T>::Remove(T &item) {
	m.lock();
	if (isEmpty())
	{
		m.unlock();
		return false;
	}
	if (head == tail)
	{
		item = head->item;
		delete head;
		head = nullptr;
		tail = nullptr;

	}
	else 
	{
		QueueItem* temp = head;
		
		item = head->item;
		head = head->next;

		delete temp;
		
	}
	m.unlock();
	return true;
}


template <typename T>
void SharedQueue<T>::Print() {
	m.lock();
	QueueItem * current = head;
	while (current != tail) {
		current->PrintQueueItem();
		current = current->next;
	}

	
	std::cout << "\n";
	m.unlock();
}

#endif /* __Lab14__SharedQueue__ */
