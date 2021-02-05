#include <atomic>


class LockFreeQueue {
private:
	size_t size = 100;
	const char* data[100];
	std::atomic<uint16_t> first = 0;
	std::atomic<uint16_t> last = 0;

	uint16_t next(uint16_t index) {
		if (index + 1 == size) {
			return 0;
		}
		else {
			return index + 1;
		}
	}

public:
	void push(const char* log) {
		if (next(last) == first) {
			std::cout << "Queue is full" << std::endl;
		}
		else
		{
			data[last] = log;
			last = next(last);
		}
	}
	
	const char* pop() {
		if (first == last) {
			std::cout << "Queue empty" << std::endl;
			return "";
		}
		else
		{
			const char* tmp = data[first];
			first = next(first);
			return tmp;
		}
	}
};