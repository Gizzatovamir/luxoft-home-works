#include <condition_variable>
#include <iostream>
#include <list>
#include <queue>
#include <thread>
#include <set>

#include <stdlib.h>
#include <time.h>


enum class event_template {
  data_produced, data_consumed
};

class subscriber {
public:
  subscriber(event_template interested_event_type) 
  : m_id(generate_id())
  , m_interested_event_type(interested_event_type) {
  }

  const event_template& get_interesed_event_type() const {
    return m_interested_event_type;
  }

  std::string to_string() const {
    return "subscriber[" + std::to_string(m_id) + "]";
  }

  virtual void on_notification(const std::string& data) const {
    std::cout << to_string() + ": " + data << std::endl;
  }

  bool operator<(const subscriber& other) const 
  {
    return m_id < other.m_id;  //assume that you compare the record based on a
  }
private:
  static int generate_id() {
    return s_id++;
  }

  static int s_id;
private:
  int m_id;
  event_template m_interested_event_type;
};
int subscriber::s_id = 0;

class data_produced_subscriber: public subscriber {
public:
  data_produced_subscriber() 
  : subscriber(event_template::data_produced) {
  }

  void on_notification(const std::string& data) const override {
    std::cout << subscriber::to_string() + " data produced: " + data << std::endl;
  }
private:
};

class data_consumed_subscriber : public subscriber {
public:
  data_consumed_subscriber() 
  : subscriber(event_template::data_consumed) {
  }

  void on_notification(const std::string& data) const override {
    std::cout << subscriber::to_string() + " data consumed: " + data << std::endl;
  }
private:
};

class publisher {
public:
  void subscribe(subscriber* subscriber) {
    std::cout << subscriber->to_string() << " subcribed" << std::endl;
    m_subscribers.insert(subscriber);
  }

  void unsubscribe(subscriber* subscriber) {
    std::cout << subscriber->to_string() << " unsubcribed" << std::endl;
    m_subscribers.erase(subscriber);
  }

  void notify_all(event_template event, const std::string& data) {
    for (const auto& subscriber : m_subscribers) {
      // notify only interested in specific event type subscribers
      if (subscriber->get_interesed_event_type() == event) {
        subscriber->on_notification(data);
      }
    }
  }

  ~publisher() {
    while (!m_subscribers.empty()) {
      unsubscribe(*m_subscribers.cbegin());
    }
  }
private:
  std::set<subscriber *> m_subscribers;
};

constexpr int k_max_loop = 10;
constexpr int default_subscribers_count = 1;

// Compiler note: the 'pthread' library shall be linked
int main()
{

  std::mutex mutex;
  std::condition_variable cv;
  std::queue<int> data;

  srand(time(NULL));
  
  int produced_sub_count;
  int consumed_sub_count;

  std::cin >> produced_sub_count >> consumed_sub_count;

  publisher publisher;
  std::vector<subscriber *> subscribers;

  for (int i = 0; i < produced_sub_count; ++i) {
    subscribers.push_back(new data_produced_subscriber());
  }

  for (int i = 0; i < consumed_sub_count; ++i) {
    subscribers.push_back(new data_consumed_subscriber());
  }
  
  for (const auto& subscriber : subscribers) {
    publisher.subscribe(subscriber);
  }

  int max_loop = 2 * (produced_sub_count + consumed_sub_count);
  
  // Events producer - each one second generate random number with range 0..99
  // Syncronization complete via condition variable
  auto worker = std::thread([&publisher, &data, &mutex, &cv, max_loop]() {
    for(int i = max_loop; i; --i){
      std::this_thread::sleep_for(std::chrono::seconds(1U));
      int newValue = rand() % 100;
      {
        std::lock_guard<std::mutex> const lock(mutex);
        data.push(newValue);
        publisher.notify_all(event_template::data_produced, std::to_string(newValue));
        cv.notify_one();
      }
    };
  });

  // Events consumer
  while(max_loop){
    std::list<int> buffer;
    {
      std::unique_lock<std::mutex> lock(mutex);
      cv.wait(lock, [&data]() {return (data.size() != 0U); } );
      while(data.size()){
        int oldValue = data.front();
        buffer.push_back(oldValue);
        publisher.notify_all(event_template::data_consumed, std::to_string(oldValue));
        data.pop();
      }
    }
    for (auto const& iter : buffer){
      std::cout << "Value from queue - " << iter << std::endl;  
    }
    --max_loop;
  }

  worker.join();

  return EXIT_SUCCESS;
}
