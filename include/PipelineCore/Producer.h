#pragma once

#include <PipelineBase/Producible.h>

template <typename OutType>
class Producer : public Producible<OutType> {
   public:
    Producer() : Producible<OutType>() {};

   protected:
    void step() override {
        OutType production = this->produce();
        this->push(production);
    }

    virtual OutType produce() = 0;
};
