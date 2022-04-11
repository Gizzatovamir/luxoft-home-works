#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <queue>
#include <condition_variable>
#include <atomic>

template <typename T, int MaxLen, typename Container=std::deque<T>>
class FixedQueue : public std::queue<T, Container> {
public:
    void push(const T& value) {
        if (this->size() == MaxLen) {
           this->c.pop_front();
        }
        std::queue<T, Container>::push(value);
    }
};

std::atomic<bool> busy(false);
FixedQueue<int,10> queue;

int produceData() {
  int randomNumber = rand() % 1000;
  std::cout << "produced data: " << randomNumber << std::endl;
  return randomNumber;
}




void consumeData(int data) { std::cout << "received data: " << data << std::endl; }

// consumer thread function
void consumer() {
  
  for(int i = 0;i<100;i++){
  bool desired = false;
  if (!queue.empty() && busy.compare_exchange_strong(desired, true)) {
        int g_data = queue.front();
        queue.pop();
        consumeData(g_data);
        busy.store(false);
      }
  
  }
}

// producer thread function
void producer() {
	for(int i = 0;i< 100;i++){
      bool desired = false;
      if (busy.compare_exchange_strong(desired, true)) {
        int g_data = produceData();
        queue.push(g_data);
        busy.store(false);
      }
	}
}

void consumerThread() { consumer(); }

void producerThread() { producer(); }

int main() {
  auto start = std::chrono::high_resolution_clock::now();
	std::thread t1(consumerThread);
	std::thread t2(producerThread);
	t1.join();
	t2.join();
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time taken by function: "
        << duration.count() << " microseconds" << std::endl;
	return 0;
}
