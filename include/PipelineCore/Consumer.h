#pragma once

#include <PipelineBase/Consumable.h>

#include <memory>

template <typename InType>
class Consumer : public Consumable<InType> {
   public:
    Consumer() : Consumable<InType>() {};

   protected:
    void step() override {
        if (!this->empty()) {
            InType x = this->front();
            this->pop();
            this->consume(x);
        }
    };

    virtual void consume(InType& x) = 0;
};