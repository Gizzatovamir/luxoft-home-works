#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <queue>
#include <condition_variable>

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

FixedQueue<int,1> queue;
std::mutex g_mutex;
std::condition_variable cv;
bool g_ready = false;

int produceData() {
  int randomNumber = rand() % 1000;
  std::cout << "produce data: " << randomNumber << "\n";
  return randomNumber;
}




void consumeData(int data) { std::cout << "receive data: " << data << "\n"; }

// consumer thread function
void consumer() {
  while (!g_ready) {
      int delay = 500;
      std::this_thread::sleep_for (std::chrono::milliseconds(delay));  
    }
  for(int i = 0;i<100;i++){
  std::unique_lock<std::mutex> ul(g_mutex);
  cv.wait(
	  ul,[]{return !queue.empty();});
  int g_data = queue.front();
  queue.pop();
  consumeData(g_data);
  g_ready = false;
  
  }
}

// producer thread function
void producer() {
	for(int i = 0;i< 100;i++){
    std::unique_lock<std::mutex> ul(g_mutex);

    int g_data = produceData();
    g_ready = true;
    queue.push(g_data);
    cv.notify_one();
    ul.unlock();
    
    while (g_ready) {
      srand( time( 0 ) );
      int rand_number = rand() % 900 + 100;
      std::this_thread::sleep_for (std::chrono::milliseconds(rand_number));
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
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
  std::cout << "Time taken by function: "
        << duration.count() << " secnds" << std::endl;
	return 0;
}
