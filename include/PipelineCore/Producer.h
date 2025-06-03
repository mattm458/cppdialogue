#pragma once

#include <PipelineBase/Producible.h>
#include <PipelineBase/Runnable.h>

template <typename OutType>
class Producer : public Producible<OutType>, public Runnable {
   public:
    Producer() : Producible<OutType>(), Runnable() {};

   protected:
    void step() override {
        OutType production = this->produce();
        this->push(production);
    }

    virtual OutType produce() = 0;
};
