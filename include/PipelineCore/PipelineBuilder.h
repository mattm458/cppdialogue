#pragma once

#include <PipelineBase/Consumable.h>
#include <PipelineBase/Producible.h>
#include <PipelineBase/Runnable.h>

#include <PipelineCore/Pipeline.h>

#include <vector>

template <class LastProducer>
class IncompletePipelineBuilder;

class PipelineBuilder {
   public:
    template <class T, class... _Args>
    static IncompletePipelineBuilder<T> BuildPipeline(_Args &&...__args) {
        static_assert(std::derived_from<T, ProducibleType> == true);
        T *p = new T(std::forward<_Args>(__args)...);

        return IncompletePipelineBuilder<T>(p);
    }

    PipelineBuilder() : pipeline(new Pipeline()) {};
    PipelineBuilder(Pipeline *pipeline) : pipeline(pipeline) {};

   protected:
    Pipeline *pipeline;
};

template <class LastProducer>
class IncompletePipelineBuilder : public PipelineBuilder {
   public:
    IncompletePipelineBuilder(LastProducer *p)
        : PipelineBuilder(), last_producer(p) {
        this->pipeline->add_stage(p);
    }

    IncompletePipelineBuilder(Pipeline *pipeline, LastProducer *p)
        : PipelineBuilder(pipeline), last_producer(p) {
        this->pipeline->add_stage(p);
    }

    template <class T, class... _Args>
    IncompletePipelineBuilder<T> then(_Args &&...__args) {
        T *p = new T(std::forward<_Args>(__args)...);
        this->last_producer->connect(*p);

        return IncompletePipelineBuilder<T>(this->pipeline, p);
    }

    template <class T, class... _Args>
    Pipeline *close(_Args &&...__args) {
        static_assert(std::derived_from<T, ConsumableType> == true);

        T *c = new T(std::forward<_Args>(__args)...);
        c->connect(*this->last_producer);
        this->pipeline->add_stage(c);

        return pipeline;
    }

   private:
    LastProducer *last_producer;
};
