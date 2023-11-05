#include <queue>
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

template <typename T>
class LockBasedQueue {
public:
    LockBasedQueue();

    void push(const T& value);

    bool try_pop(T& value);

    void wait_and_pop(T& value);

    bool empty() const;

private:
    std::queue<T> data_queue;
    mutable std::mutex mutex;
    std::condition_variable condition;
};

// ------------------------------------

template <typename T>
LockBasedQueue<T>::LockBasedQueue() {}

template <typename T>
void LockBasedQueue<T>::push(const T& value) {
    {
        std::lock_guard<std::mutex> lock(mutex);
        data_queue.push(value);
    }
    condition.notify_one();
}

template <typename T>
bool LockBasedQueue<T>::try_pop(T& value) {
    std::lock_guard<std::mutex> lock(mutex);
    if (data_queue.empty()) {
        return false;
    }
    value = data_queue.front();
    data_queue.pop();
    return true;
}

template <typename T>
void LockBasedQueue<T>::wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock, [this] { return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
}

template <typename T>
bool LockBasedQueue<T>::empty() const {
    std::lock_guard<std::mutex> lock(mutex);
    return data_queue.empty();
}

// ------------------------------------


template <typename T>
class LockFreeQueue {
public:
    LockFreeQueue();

    void push(const T& value);

    bool try_pop(T& value);

    bool empty() const;

private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;
};

// ------------------------------------

template <typename T>
LockFreeQueue<T>::LockFreeQueue() : head(nullptr), tail(nullptr) {}

template <typename T>
void LockFreeQueue<T>::push(const T& value) {
    Node* new_node = new Node(value);
    Node* prev_tail = tail.load();
    new_node->next = nullptr;
    while (true) {
        Node* last = tail.load();
        if (tail.compare_exchange_weak(last, new_node)) {
            if (prev_tail) {
                prev_tail->next = new_node;
            } else {
                head.store(new_node);
            }
            return;
        }
    }
}

template <typename T>
bool LockFreeQueue<T>::try_pop(T& value) {
    Node* first = head.load();
    while (first && !head.compare_exchange_weak(first, first->next)) {
        // Keep looping until successfully popping or head changes
    }
    if (first) {
        value = first->data;
        delete first;
        return true;
    }
    return false;
}

template <typename T>
bool LockFreeQueue<T>::empty() const {
    return head.load() == nullptr;
}

// ------------------------------------


const int num_producers = 3;
const int num_consumers = 2;
const int num_items_per_producer = 5;
const int num_items_per_consumer = 7;

LockBasedQueue<int> lockBasedQueue;
LockFreeQueue<int> lockFreeQueue;

void lockBasedProducer(int id) {
    for (int i = 0; i < num_items_per_producer; ++i) {
        int value = id * num_items_per_producer + i;
        lockBasedQueue.push(value);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void lockBasedConsumer(int id) {
    for (int i = 0; i < num_items_per_consumer; ++i) {
        int value;
        while (!lockBasedQueue.try_pop(value)) {
            // Keep trying to pop until successful
        }
        std::cout << "Lock-Based Consumer " << id << " Popped: " << value << std::endl;
    }
}

void lockFreeProducer(int id) {
    for (int i = 0; i < num_items_per_producer; ++i) {
        int value = id * num_items_per_producer + i;
        lockFreeQueue.push(value);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void lockFreeConsumer(int id) {
    for (int i = 0; i < num_items_per_consumer; ++i) {
        int value;
        while (!lockFreeQueue.try_pop(value)) {
            // Keep trying to pop until successful
        }
        std::cout << "Lock-Free Consumer " << id << " Popped: " << value << std::endl;
    }
}

int main() {
    std::vector<std::thread> lockBasedProducers;
    std::vector<std::thread> lockBasedConsumers;
    std::vector<std::thread> lockFreeProducers;
    std::vector<std::thread> lockFreeConsumers;

    // Create lock-based producer and consumer threads
    for (int i = 0; i < num_producers; ++i) {
        lockBasedProducers.emplace_back(lockBasedProducer, i);
    }

    for (int i = 0; i < num_consumers; ++i) {
        lockBasedConsumers.emplace_back(lockBasedConsumer, i);
    }

    // Create lock-free producer and consumer threads
    for (int i = 0; i < num_producers; ++i) {
        lockFreeProducers.emplace_back(lockFreeProducer, i);
    }

    for (int i = 0; i < num_consumers; ++i) {
        lockFreeConsumers.emplace_back(lockFreeConsumer, i);
    }

    // Join all threads

    for (auto& producer_thread : lockBasedProducers) {
        producer_thread.join();
    }

    for (auto& consumer_thread : lockBasedConsumers) {
        consumer_thread.join();
    }

    for (auto& producer_thread : lockFreeProducers) {
        producer_thread.join();
    }

    for (auto& consumer_thread : lockFreeConsumers) {
        consumer_thread.join();
    }

    return 0;
}














































