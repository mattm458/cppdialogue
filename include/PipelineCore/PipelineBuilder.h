#pragma once

#include <PipelineBase/Consumable.h>
#include <PipelineBase/Producible.h>
#include <PipelineBase/Runnable.h>

#include <PipelineCore/Pipeline.h>

#include <memory>
#include <vector>

template <class LastProducer>
class TypedPipelineBuilder;

class PipelineBuilder {
   public:
    template <class T, class... _Args>
    static std::shared_ptr<TypedPipelineBuilder<T>> BuildPipeline(
        _Args&&... __args) {
        static_assert(std::derived_from<T, ProducibleType> == true);

        std::shared_ptr<T> producer =
            std::make_shared<T>(std::forward<_Args>(__args)...);

        std::shared_ptr<std::vector<std::shared_ptr<Runnable>>> stages =
            std::make_shared<std::vector<std::shared_ptr<Runnable>>>();
        stages->push_back(producer);

        return std::make_shared<TypedPipelineBuilder<T>>(producer, stages);
    }

    PipelineBuilder()
        : stages(std::make_shared<std::vector<std::shared_ptr<Runnable>>>()) {}
    PipelineBuilder(
        std::shared_ptr<std::vector<std::shared_ptr<Runnable>>> stages)
        : stages(stages) {}

   protected:
    std::shared_ptr<std::vector<std::shared_ptr<Runnable>>> stages;
};

template <class LastProducer>
class TypedPipelineBuilder : public PipelineBuilder {
   public:
    TypedPipelineBuilder(
        std::shared_ptr<LastProducer> last_producer,
        std::shared_ptr<std::vector<std::shared_ptr<Runnable>>> stages)
        : PipelineBuilder(stages), last_producer(last_producer) {}

    template <class T, class... _Args>
    std::shared_ptr<TypedPipelineBuilder<T>> then(_Args&&... __args) {
        std::shared_ptr<T> producer =
            std::make_shared<T>(std::forward<_Args>(__args)...);

        last_producer->connect(*producer);
        this->stages->push_back(producer);

        return std::make_shared<TypedPipelineBuilder<T>>(producer, stages);
    }

    template <class T, class... _Args>
    Pipeline close(_Args&&... __args) {
        static_assert(std::derived_from<T, ConsumableType> == true);

        std::shared_ptr<T> producer =
            std::make_shared<T>(std::forward<_Args>(__args)...);

        this->stages->push_back(producer);

        return Pipeline(stages);
    }

   private:
    std::shared_ptr<LastProducer> last_producer;
};
