#pragma once

#include <mutex>
#include <queue>
#include <utility>

template <class T>
class MutexQueue {
   public:
    bool empty() {
        this->mtx.lock();
        bool e = this->queue.empty();
        this->mtx.unlock();
        return e;
    };

    T& front() {
        this->mtx.lock();
        T& f = this->queue.front();
        this->mtx.unlock();
        return f;
    }

    void push(const T& val) {
        this->mtx.lock();
        this->queue.push(val);
        this->mtx.unlock();
    }

    template <class... Args>
    void emplace(Args&&... args) {
        this->mtx.lock();
        this->queue.emplace(std::forward<Args>(args)...);
        this->mtx.unlock();
    }

    void pop() {
        this->mtx.lock();
        this->queue.pop();
        this->mtx.unlock();
    }

   private:
    std::mutex mtx;
    std::queue<T> queue;
};