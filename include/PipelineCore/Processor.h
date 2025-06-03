#pragma once

#include <PipelineBase/Consumable.h>
#include <PipelineBase/Producible.h>
#include <PipelineBase/Runnable.h>

template <typename InType, typename OutType>
class Processor : public Consumable<InType>,
                  public Producible<OutType>,
                  public Runnable {
   public:
    Processor() : Consumable<InType>(), Producible<OutType>(), Runnable() {};

   protected:
    void step() override {
        if (!this->empty()) {
            InType in = this->front();
            this->pop();

            OutType out = this->process(in);
            this->push(out);
        }
    }

    virtual OutType process(InType &in) = 0;
};