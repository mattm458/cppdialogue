#pragma once

#include <PipelineCore/MutexQueue.h>
#include <PipelineCore/Runnable.h>

#include <memory>

template <class OutType>
class Producer;

template <typename InType>
class Consumer : public Runnable {
   public:
    Consumer()
        : has_producer(false),
          consumer_queue(std::make_shared<MutexQueue<InType>>()) {}
    Consumer(const Producer<InType>& producer)
        : has_producer(true), consumer_queue(producer.get_producer_queue()) {}

    void set_producer(Producer<InType>& producer) {
        if (this->has_producer)
            throw std::runtime_error("This Consumer already has a Producer!");

        this->has_producer = true;
        this->consumer_queue = producer.get_producer_queue();
    }

    std::shared_ptr<MutexQueue<InType>> get_consumer_queue() const {
        return this->consumer_queue;
    };

   protected:
    bool consumable() { return !this->consumer_queue->empty(); }
    InType consume() {
        InType t = this->consumer_queue->front();
        this->consumer_queue->pop();
        return t;
    }

   private:
    bool has_producer;
    std::shared_ptr<MutexQueue<InType>> consumer_queue = nullptr;
};