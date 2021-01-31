#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include<queue>
#include<mutex>
#include<condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
	mutable std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;

public:
	ThreadSafeQueue()
	{}
	void push(T new_value) {
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(std::move(new_value));
		data_cond.notify_one();
	}

	void wait_and_pop(T& value) {
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		value = std::move(data_queue.front());
		data_queue.pop();
	}


};


#endif