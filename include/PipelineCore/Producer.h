#pragma once

#include <PipelineCore/MutexQueue.h>
#include <PipelineCore/Runnable.h>

#include <iostream>
#include <memory>

template <class InType>
class Consumer;

template <typename OutType>
class Producer : public Runnable {
   public:
    Producer()
        : has_consumer(false),
          producer_queue(std::make_shared<MutexQueue<OutType>>()) {}
    Producer(const Consumer<OutType>& consumer)
        : has_consumer(true), producer_queue(consumer.get_consumer_queue()) {}

    void set_consumer(Consumer<OutType>& consumer) {
        if (this->has_consumer)
            throw std::runtime_error("This Producer already has a Consumer!");

        this->has_consumer = true;
        this->producer_queue = consumer.get_consumer_queue();
    }

    std::shared_ptr<MutexQueue<OutType>> get_producer_queue() const {
        return this->producer_queue;
    };

   protected:
    void produce(OutType& x) { this->producer_queue->push(x); }

   private:
    int count = 20;
    bool has_consumer;
    std::shared_ptr<MutexQueue<OutType>> producer_queue = nullptr;
};