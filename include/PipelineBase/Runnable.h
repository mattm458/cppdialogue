#pragma once

#include <atomic>
#include <future>
#include <iostream>

class Runnable {
   public:
    virtual ~Runnable() { this->stop(); }

    std::future<void> start() {
        this->pre_startup();
        this->running.test_and_set();
        return std::async(std::launch::async, &Runnable::_start, this);
    }

    void stop() { this->running.clear(); }

   protected:
    void _start() {
        this->post_startup();
        while (this->running.test()) {
            this->step();
            std::this_thread::yield();
        }
    }

    virtual void step() = 0;
    virtual void pre_startup() {};
    virtual void post_startup() {};

   private:
    std::atomic_flag running;
};