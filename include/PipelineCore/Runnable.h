#pragma once

#include <thread>

class Runnable {
   public:
    ~Runnable() {
        if (this->t.joinable()) {
            this->stop();
            this->t.join();
        }
    }

    void start() {
        this->running = true;

        this->t = std::thread(&Runnable::_start, this);
    }

    void _start() {
        while (this->running) {
            this->step();
            std::this_thread::yield();
        }

        this->running = false;
    }

    void stop() { this->running = false; }

    bool is_running() const { return this->running; }

    virtual void step() = 0;

   private:
    bool running = false;
    std::thread t;
};