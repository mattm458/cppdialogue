#pragma once

#include <PipelineBase/MutexQueue.h>

#include <memory>

class ConsumableType {};

template <class OutType>
class Producible;

template <class InType>
class Consumable : public ConsumableType {
   public:
    Consumable()
        : ConsumableType(),
          has_producer(false),
          consumer_queue(std::make_shared<MutexQueue<InType>>()) {}

    void connect(Producible<InType>& producer) {
        if (this->has_producer)
            throw std::runtime_error("This Consumer already has a Producer!");

        this->has_producer = true;
        producer.has_consumer = true;
        this->consumer_queue = producer.producer_queue;
    }

   protected:
    bool empty() { return this->consumer_queue->empty(); }
    InType& front() { return this->consumer_queue->front(); }
    void pop() { this->consumer_queue->pop(); }

   private:
    friend class Producible<InType>;
    bool has_producer;
    std::shared_ptr<MutexQueue<InType>> consumer_queue = nullptr;
};