#pragma once

#include <PipelineBase/MutexQueue.h>

#include <iostream>
#include <memory>

template <class InType>
class Consumable;

template <typename OutType>
class Producible {
   public:
    Producible()
        : has_consumer(false),
          producer_queue(std::make_shared<MutexQueue<OutType>>()) {}

    void connect(Consumable<OutType>& consumer) {
        if (this->has_consumer)
            throw std::runtime_error("This Producer already has a Consumer!");

        this->has_consumer = true;
        consumer.has_producer = true;
        this->producer_queue = consumer.consumer_queue;
    }

   protected:
    void push(OutType& x) { this->producer_queue->push(x); }

   private:
    friend class Consumable<OutType>;
    bool has_consumer;
    std::shared_ptr<MutexQueue<OutType>> producer_queue = nullptr;
};